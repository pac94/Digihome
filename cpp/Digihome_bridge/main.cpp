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

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno,serial_fd ;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     Led led("chambre",2,3,4);
     int tab[20];
     int val = led.To_serial_format(tab);
     for(int i = 0;i < val; i++)
     {
        cout << tab[i]<<endl;
     }

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
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     Json::Value root;
     Json::Reader reader;
     bool parsedSuccess = reader.parse(buffer,root,false);
     if(not parsedSuccess)
     {
        cout<<"failed"<<endl;
     }
     else
     {
        const Json::Value sensor = root["sensor"];
        const Json::Value status = root["status"];
        const Json::Value room = root["room"];
        if(not sensor.isNull())
        {
            cout<< "sensor :"<< sensor.asString()<< " status :"
            <<status.asString()<< " room : "<< room.asString()<<endl;

        }
        serial_fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

        if (serial_fd==-1) {
        printf ("Error opening the serial device: /dev/ttyUSB0");
        perror("OPEN");
        exit(0);
        }

        struct termios tty;
        memset (&tty, 0, sizeof tty);

        /* Set Baud Rate */
        cfsetospeed (&tty, B9600);
        cfsetispeed (&tty, B9600);

        /* Setting other Port Stuff */
        tty.c_cflag     &=  ~PARENB;        // Make 8n1
        tty.c_cflag     &=  ~CSTOPB;
        tty.c_cflag     &=  ~CSIZE;
        tty.c_cflag     |=  CS8;
        tty.c_cflag     &=  ~CRTSCTS;       // no flow control
        tty.c_lflag     =   0;          // no signaling chars, no echo, no canonical processing
        tty.c_oflag     =   0;                  // no remapping, no delays
        tty.c_cc[VMIN]      =   0;                  // read doesn't block
        tty.c_cc[VTIME]     =   5;                  // 0.5 seconds read timeout

        tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines
        tty.c_iflag     &=  ~(IXON | IXOFF | IXANY);// turn off s/w flow ctrl
        tty.c_lflag     &=  ~(ICANON | ECHO | ECHOE | ISIG); // make raw
        tty.c_oflag     &=  ~OPOST;              // make raw

        /* Flush Port, then applies attributes */
        tcflush( serial_fd, TCIFLUSH );

        if ( tcsetattr ( serial_fd, TCSANOW, &tty ) != 0)
        {
        cout << "Error " << errno << " from tcsetattr" << endl;
        }

        //Now the port is ready to work
        //Write anything you want to the port;
        //It`s stored in buf
        char send[3] = "a";
        write (serial_fd, &send, 1);
        printf("Error description is : %s\n",strerror(errno));
        //Finally, you close the port
        close(serial_fd);
             }
    string receive_buffer = "{\"error\" : \"ok\"}";
    char *cstr = new char[receive_buffer.length() + 1];
    strcpy(cstr, receive_buffer.c_str());
     n = write(newsockfd,cstr,receive_buffer.length());
     printf("n : %d", n);
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     }
     close(sockfd);
     return 0;
}
