using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;

class Program
{
    static void Main(string[] args)
    {
        // 服务器地址和端口号
        IPAddress ipAddress = IPAddress.Parse("127.0.0.1");
        int port = 8000;

        // 读取txt2内容
        //文件地址 "E:\my\socket\2\txt2.txt" 请修改为自己的文件地址
        string sendData = File.ReadAllText("E:/my/socket/2/txt2.txt");
        // Console.WriteLine("send data2 from c#: ");
        // Console.WriteLine(sendData);

        // 创建TCP监听器并开始监听连接请求
        TcpListener listener = new TcpListener(ipAddress, port);
        listener.Start();

        Console.WriteLine("Waiting for client...");

        // 等待客户端连接
        TcpClient client = listener.AcceptTcpClient();
        Console.WriteLine("Client connected");

        // 获取与客户端通信的网络流
        NetworkStream stream = client.GetStream();

        // 读取客户端发送的数据txt1
        byte[] buffer_rev = new byte[1024];
        int bytesRead = stream.Read(buffer_rev, 0, buffer_rev.Length);
        string receivedData = Encoding.ASCII.GetString(buffer_rev, 0, bytesRead);
        Console.WriteLine("Received data from client: " + receivedData);

        // 发送txt2文本文件内容给C++
        byte[] buffer = Encoding.ASCII.GetBytes(sendData);
        stream.Write(buffer, 0, buffer.Length);
        
        Console.WriteLine("Sent data to client: " + sendData);

        // 关闭网络流和客户端连接
        stream.Close();
        client.Close();
        listener.Stop();

        Console.WriteLine("Press any key to exit");
        Console.ReadKey();
    }
}
