#include <iostream>
#include "Networking.h"
#include "UdpConnectionManager.h"

class UdpTester : public Lii::Api::ReceiverSubscriber
{
public:
    void OnStreamStarted(unsigned char *streamBuffer, unsigned int size) override
    {
        std::cout << "Received data: " << size << std::endl;
    }

public:

};

std::unique_ptr<unsigned char> GenerateTestData(unsigned int size)
{
    auto* data = new unsigned char[size];
    for(unsigned int i = 0; i < size; i++)
        data[i] = i;

    return std::unique_ptr<unsigned char>(data);
}

int main()
{
    Lii::Networking::Init();
    UdpTester tester{};
    auto testDataSize = 100000;
    auto data = GenerateTestData(testDataSize);
    auto listenSocket = Lii::Udp::UdpConnectionManager("127.0.0.1", 20015);
    auto sendSocket = Lii::Udp::UdpConnectionManager("127.0.0.1", 20016);
    sendSocket.SetDestination("127.0.0.1", 20015);

    listenSocket.AddReceiverSubscriber(tester);
    listenSocket.StartConcurrentReceive();

    sendSocket.SendData(data.get(), testDataSize);
    listenSocket.WaitForReceiveThread();

    return 0;
}
