#ifndef MYSERVER_H_INCLUDED
#define MYSERVER_H_INCLUDED
/*
   UDP server module.
   the purpose of this module is to implement the UDP server functionality
   Currently not all optios are implemented but from interface perspectives this module could be extended for
   future requirment.
*/



/* Define Server Type
  ReplayType    - No special processing, just replay what you get
                  Currently the only implemented option
  ProcessType1  - for future infra-structure , could be used for getting the message and processed it with
                  related to some algorithm that is based on the client address
                  not implemented
  ProcessType2  - for future infra-structure - could be used for encryptions , getting the data and convert it for security purpose
                  not implemented yet
*/
typedef enum  {
   ReplayType,
   ProcessType1,
   ProcessType2
} ServerType ;



/* Define Server Error type  on initialization
  ServerOK    -   No Error
  ProcessTypeNotImplemented - getting Server type which is not supported yet
  ErrorWhileCreatingUDPSocket - Error while openning the socket , if you get this you need to close the server using closeServer()
  ErrorWhileBindingUDPSocket  - Error while openning the socket , if you get this you need to close the server using closeServer()
  ErrorWhileRecvFromUDPSocket - Error while openning the socket , if you get this you need to close the server using closeServer()
  ErrorWhileSendTOUDPSocket   - Error while openning the socket , if you get this you need to close the server using closeServer()


*/


typedef enum  {
   ServerOK,
   ProcessTypeNotImplemented,
   ErrorWhileCreatingUDPSocket,
   ErrorWhileBindingUDPSocket,
   ErrorWhileRecvFromUDPSocket,
   ErrorWhileSendTOUDPSocket
} ServerErrorCode ;




/*
    Written By Eyal.Yehieli
    initServer - The purpose of this function is to initalize the Server module with respect to operation modes.
    input parameters:
        ServerType - Server tpye as described in typedef enum ServerType (currently only first option is implemented)
        int - Port number - The server UDP socket port number
*/
ServerErrorCode initServer(int PortNumber,ServerType ServerT);

/*
      Written By Eyal.Yehieli
      Currently  only replay mode  is supported.
      future feature that the server optionally will support is related to new requirments.
      The Server is processed for ever and retrun back only if error is happening.
*/
ServerErrorCode ProcessingServer(void);


/*
   cleaning module open resources.
   This function should be called in when any error from Server module is return.

*/
ServerErrorCode closeServer(void);



#endif // MYSOCKET_H_INCLUDED
