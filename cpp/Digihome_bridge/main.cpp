#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <jsoncpp/json.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include "include/Led.h"
#include "include/Equipement.h"
#include "include/Chauffage.h"
#include "include/Moteur.h"
#include <sstream>

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}


int main(int argc, char *argv[])
{
    vector<Equipement*> liste;
    int sockfd, newsockfd, portno, serial_fd ;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     uint8_t test[30],numb,buf = 0;
     string receive_buffer = "{\"error\" : \"ok\"}";
     //Led led("chambre",2,3,4);
     liste.push_back(new Led("chambre",2,3,4));
     liste.push_back(new Led("chambre1",5,6,7));
     liste.push_back(new Chauffage("salon",5));
     liste.push_back(new Moteur("cuisine",7));
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
            stringstream ss;
            ss << "{\"error\" :\"ok\", \"state\": [";
            for(int j = 0; j < 2; j++)
            {
                int sendcolor = dynamic_cast<Led*>(liste[j])->Get_led_color();
                string mystatus = "off";
                if(sendcolor)
                    mystatus = "on";
                ss << "{ \"sensor\":\"" << liste[j]->Gettype() << "\", \"status\":\"" << mystatus << "\",\"color\":" << sendcolor << ",\"room\":\"" << liste[j]->Getroom() <<"\" }";
                if(j == 0)
                    ss << ",";

            }
            ss << "]}";
            receive_buffer = ss.str();
            test[0] = 0x7E;
            test[1] = 0x01;
            test[2] = 0x03;
            test[3] = 0xE7;
            numb = 4;

        }
        if(cmd.asInt() == 1)
        {
            const Json::Value sensor = root["sensor"];
        const Json::Value status = root["status"];
        const Json::Value room = root["room"];



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

            for(int i = 0;i < 3; i++)
            {
                if((sensor.asString().compare(liste[i]->Gettype()) == 0) && (room.asString().compare(liste[i]->Getroom()) == 0))
                {


                                dynamic_cast<Led*>(liste[i])->Set_led_color(col[0],col[1],col[2]);
                                    numb = liste[i]->ToArduinoFormat(test);

                    break;
                }
                else
                    cout << "error comapre" << endl;


        }
        }
        serial_fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY  |   O_NONBLOCK);

        if (serial_fd==-1) {
        printf ("Error opening the serial device: /dev/ttyUSB0");
        perror("OPEN");
        exit(0);
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

        ssize_t nbwriten = write (serial_fd, &test, numb);
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
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

while(select(serial_fd + 1, &read_fds, &write_fds, &except_fds, &timeout) > 0)
        {
            int res = read(serial_fd,&receiveBytes,200);
            if(res == -1)
                printf("%s",strerror(errno));
            else{
                for(int i = 0; i < res; i++)
                    printf("res[%d] = %d\n",i, receiveBytes[i]);
            }

        }
        /*else
        {

            printf("timeout\n");

        }*/



        close(serial_fd);

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
