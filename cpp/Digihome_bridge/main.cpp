#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <jsoncpp/json.h>
#include <jsoncpp/writer.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include "include/Led.h"
#include "include/Equipement.h"
#include "include/Chauffage.h"
#include "include/Moteur.h"
#include "include/Capteur.h"
#include <sstream>

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
int serialTransfert(uint8_t* buffwrt, uint8_t nbwrt, uint8_t* buffread);
string getState();
string setState(Json::Value root);
vector<Equipement*> liste;
string receive_buffer;
int main(int argc, char *argv[])
{

    int sockfd, newsockfd, portno, serial_fd ;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     uint8_t test[30],numb,buf = 0, test2[200];
     receive_buffer = "{\"error\" : \"ok\"}";
     //Led led("chambre",2,3,4);
     liste.push_back(new Led("piece1",2,3,4));
     liste.push_back(new Led("piece2",5,6,7));
     liste.push_back(new Led("piece3",8,8,8));
     liste.push_back(new Chauffage("piece2",13));
     liste.push_back(new Moteur("piece3",12,11));
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi("9494");
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     while(1)
     {
             newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);
     if (newsockfd < 0)
          error("ERROR on accept");
    else
        cout << "new accept" << endl;
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
    // printf("Here is the message: %s\n",buffer);
     Json::Value root;
     Json::Reader reader;
     bool parsedSuccess = reader.parse(buffer,root,false);
     if(not parsedSuccess)
     {
        printf("failed\n");
     }
     else
     {

        const Json::Value cmd = root["cmd"];
        printf("CMD = %d\n",cmd.asInt());
        if(cmd.asInt() == 3)
        {
            receive_buffer = getState();
        }
        if(cmd.asInt() == 1)
        {
            receive_buffer = setState(root);
        }


        }


    char *cstr = new char[receive_buffer.length() + 1];
    strcpy(cstr, receive_buffer.c_str());
    printf("%s\n", cstr);
     n = write(newsockfd,cstr,receive_buffer.length());
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     }
     close(sockfd);
     return 0;
}


int serialTransfert(uint8_t* buffwrt, uint8_t nbwrt, uint8_t* buffread)
{
    int serial_fd;
            serial_fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY  |   O_NONBLOCK);

        if (serial_fd==-1) {
        printf ("Error opening the serial device: /dev/ttyUSB0");
        perror("OPEN");
        //exit(0);
        return -1;
        }

        struct termios tty;
        memset (&tty, 0, sizeof tty);


        cfsetospeed (&tty, B9600);
        cfsetispeed (&tty, B9600);

    tty.c_cflag |= B9600 ;
    tty.c_cflag     &=  ~PARENB;        // Make 8n1
    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;
    tty.c_lflag &= ~ICANON;
    tty.c_cflag     &=  ~CRTSCTS;       // no flow control

     /* positionne le mode de lecture (non canonique, sans echo, ...) */
     tty.c_lflag = 0;

     tty.c_cc[VTIME]    = 100;   /* timer inter-caractÃ¨res non utilisÃ© */
     tty.c_cc[VMIN]     = 0;   /* read bloquant jusqu'Ã  ce que 5 */
                                  /* caractÃ¨res soient lus */
    cfmakeraw(&tty);
     tcflush(serial_fd, TCIFLUSH);
     tcsetattr(serial_fd,TCSANOW,&tty);

        ssize_t nbwriten = write (serial_fd, buffwrt, nbwrt);
            printf("Error description is : %s\n",strerror(errno));
        //Finally, you close the por
        int n = 0;
std::string response;


fd_set read_fds, write_fds, except_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    FD_ZERO(&except_fds);
    FD_SET(serial_fd, &read_fds);
    uint8_t receiveBytes[200];
    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    uint8_t offset = 0;
while(select(serial_fd + 1, &read_fds, &write_fds, &except_fds, &timeout) > 0)
        {
            int res = read(serial_fd,buffread + offset,200);
            if(res == -1)
                printf("%s",strerror(errno));
            else{
                offset += res;

            }

        }

        close(serial_fd);
        return offset;
}

string getState()
{
    uint8_t test[10], test2[200];
    Capteur* temp = new Capteur("piece2", "temperature",0.0);
    Capteur* mouv = new Capteur("piece1", "motion",0.0);
    Capteur* pres = new Capteur("piece1", "pressure",0.0);
    test[0] = 0x7E;
    test[1] = 0x01;
    test[2] = 0x03;
    test[3] = 0xE7;
    uint8_t numb = 4;

    int retrun = serialTransfert(test, numb, test2);
    if(retrun == -1)
        return "{\"error\" : \"connexion echouee\"}";

         for(int i = 0; i < retrun; i++)
                    printf("test2[%d] = %d\n",i, test2[i]);

dynamic_cast<Led*>(liste[0])->Set_led_color(test2[3],test2[4],test2[5]);
dynamic_cast<Led*>(liste[1])->Set_led_color(test2[6],test2[7],test2[8]);
dynamic_cast<Led*>(liste[2])->Set_led_color(test2[9],test2[9],test2[9]);

dynamic_cast<Moteur*>(liste[4])->set_pin_state(test2[15], test2[16]);
Json::Value event;
Json::Value led1 = dynamic_cast<Led*>(liste[0])->ToJsonFormat();
Json::Value led2 = dynamic_cast<Led*>(liste[1])->ToJsonFormat();
Json::Value led3 = dynamic_cast<Led*>(liste[2])->ToJsonFormat();
Json::Value motor = dynamic_cast<Moteur*>(liste[4])->ToJsonFormat();
Json::Value ac = dynamic_cast<Chauffage*>(liste[3])->ToJsonFormat();
Json::Value tempsens;
temp->Setvalue((float)(test2[10] *100 + test2[11])/100);
mouv->Setvalue((float)test2[12]);
pres->Setvalue((float)(test2[13] *100 + test2[14])/100);
    Json::Value vec(Json::arrayValue);
    vec.append(led1);
    vec.append(led2);
    vec.append(led3);
    vec.append(motor);
    vec.append(ac);
    vec.append(temp->ToJsonFormat());
    vec.append(mouv->ToJsonFormat());
    vec.append(pres->ToJsonFormat());
    event["error"] = "ok";
    event["state"]= vec;
    cout << event << endl;
    Json::FastWriter fastWriter;
    string jsonMessage = fastWriter.write(event);


    return jsonMessage;
}

string setState(Json::Value root)
{
    uint8_t test[50], test2[200];


    uint8_t numb = 4;
                const Json::Value sensor = root["sensor"];

        const Json::Value room = root["location"];





            for(int i = 0;i < liste.size(); i++)
            {
                if((sensor.asString().compare(liste[i]->Gettype()) == 0) && (room.asString().compare(liste[i]->Getroom()) == 0))
                {

                    if(sensor.asString() == "led")
                    {
                        const Json::Value colorval = root["color"];
                        int color = colorval.asInt();
                        int col[3];
                        if(color /4)
                        {
                            col[0] = 1;
                            color = color % 4;
                        }
                        else
                            col[0] = 0;

                        if(color /2)
                        {
                            col[1] = 1;
                            color = color % 2;
                        }
                        else
                            col[1] = 0;

                        if(color /1)
                        {
                            col[2] = 1;
                        }
                        else
                            col[2] = 0;
                        dynamic_cast<Led*>(liste[i])->Set_led_color(col[0],col[1],col[2]);
                                    numb = liste[i]->ToArduinoFormat(test);
                    }
                    if(sensor.asString() == "motor")
                    {printf("motor\n");
                        const Json::Value val = root["value"];
                        int intVal = val.asInt();
                        dynamic_cast<Moteur*>(liste[i])->set_motor_value(intVal);
                                    numb = liste[i]->ToArduinoFormat(test);
                    }

                    if(sensor.asString() == "ac")
                    {


                        const Json::Value val = root["value"];
                        int intVal = val.asInt();
                        if(intVal == 0)
                         dynamic_cast<Chauffage*>(liste[i])->eteindre();
                        else
                         dynamic_cast<Chauffage*>(liste[i])->allumer();
                                    numb = liste[i]->ToArduinoFormat(test);
                    }


                    break;
                }
                else
                    cout << "error compare" << endl;


        }
        for(int i = 0; i < numb; i++)
                    printf("test[%d] = %d\n",i, test[i]);
        int retrun = serialTransfert(test, numb, test2);
    if(retrun == -1)
        return "{\"error\" : \"connexion echouee\"}";

         for(int i = 0; i < retrun; i++)
                    printf("test2[%d] = %d\n",i, test2[i]);

                    return "{\"error\" : \"ok\"}";
}
