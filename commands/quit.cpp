#include "../Server.hpp"

void Server::quit(Client *client, Message *msg) 
{
    std::string quit_msg = "See ya!";
    if (!msg->params.empty())   // quit 메세지가 존재할 때
        quit_msg = msg->params[0];
    
    client->sendMsg(RPL_QUIT(client->getNickname(), client->getUsername(), client->getHostname(), quit_msg));

    std::vector<Channel *> channels = client->getJoinedChannels();
    std::vector<Channel *>::iterator iter = channels.begin();
    for ( ; iter != channels.end(); ++iter)  // 해당 클라이언트가 속해있는 채널들
	{
		(*iter)->removeClient(client);          // 채널에서 클라이언트 제거 
		client->sendMsgToChannel(RPL_QUIT(client->getNickname(), client->getUsername(), client->getHostname(), quit_msg), *iter);
        if ((*iter)->getClients().empty())      // 채널 안에 클라이언트가 0명일 때
            delChannel((*iter)->getName());     // 채널 삭제
    }
    delClient(client);  // 서버에서 클라이언트 삭제
}
