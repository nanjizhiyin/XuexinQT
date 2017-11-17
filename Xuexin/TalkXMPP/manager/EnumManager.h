#ifndef ENUMMANAGER_H
#define ENUMMANAGER_H

class XXEnum
{
public:
    enum XXMessageSendStatus
    {
        XXMessageSendSending=0,//发送中
        XXMessageSendSuccess,//发送成功
        XXMessageSendFail//发送失败
    };

    enum XXChatType
    {
        XXChatNone = 0,//没有类型
        XXChatPersonal,//个人
        XXChatGroup,//讨论组
        XXChatClass,//班级消息
        XXChatPubAccount,//公众号消息
        XXChatSNS //主题群消息
    };
};
#endif // ENUMMANAGER_H


