#include <ros/ros.h>

#include <fcntl.h>      // open()
#include <unistd.h>     // read(), close()
#include <termios.h>    // 串口配置
#include <cstring>
#include <iostream>

#include <my_msgs/uwb_type.h>
#include <uwb_read/lib.hpp>

int main(int argc, char** argv)
{
    // 1. ROS 初始化
    ros::init(argc, argv, "read_uwb_node");
    ros::NodeHandle nh;

    // 2.创建一个发送 <my_msgs/uwb_type> 的 publisher
    ros::Publisher pub = nh.advertise<my_msgs::uwb_type>("uwb_data", 10);

    // 3. 打开串口
    const char* port = "/dev/ttyUSB0";
    int fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd < 0)
    {
        ROS_ERROR("Failed to open %s", port);
        return -1;
    }

    ROS_INFO("Successfully opened %s", port);

    // 3. 配置串口参数
    struct termios options;
    tcgetattr(fd, &options);

    // 设置波特率（根据你的 UWB 实际情况改）
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    // 8N1
    options.c_cflag &= ~PARENB;   // 无校验
    options.c_cflag &= ~CSTOPB;   // 1 位停止位
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;       // 8 位数据位

    // 关闭硬件流控
    options.c_cflag &= ~CRTSCTS;

    // 开启接收 & 本地模式
    options.c_cflag |= (CLOCAL | CREAD);

    // 原始模式（非常关键）
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_oflag &= ~OPOST;

    // 设置生效
    tcsetattr(fd, TCSANOW, &options);

    // 4. 读取数据
    char buffer[256];

    ros::Rate rate(50); // 50 Hz 轮询

    while (ros::ok())
    {
        memset(buffer, 0, sizeof(buffer));

        int n = read(fd, buffer, sizeof(buffer) - 1);

        if (n > 0)
        {
            std::string s(buffer, n);

            double a = 0.0, d = 0.0;
            bool ok_a = extractDoubleField(s, "a", a);
            bool ok_d = extractDoubleField(s, "d", d);

            if (ok_a && ok_d)
            {
                my_msgs::uwb_type msg;
                msg.angle = a;
                msg.distance = d;

                pub.publish(msg);
            }
            else
            {
                ROS_WARN("Failed to extract fields from: %s", s.c_str());
            }
        }

        // if (n > 0)
        // {
        //     ROS_INFO_STREAM(buffer);
        // }

        ros::spinOnce();
        rate.sleep();
    }

    // 5. 关闭串口
    close(fd);
    return 0;
}
