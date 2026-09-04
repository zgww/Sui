#include <opencv2/opencv.hpp>
#include <iostream>

int mainImShow(int argc, char** argv) {
    // 检查命令行参数
    //if (argc != 2) {
    //    std::cerr << "用法: " << argv[0] << " <图片路径>" << std::endl;
    //    return -1;
    //}

    const char* image_path = "House_1_Wood_Base_Blue.png";//argv[1];

    // 1. 读取图片 (cv::IMREAD_COLOR 表示以彩色模式读取)
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

    // 2. 检查图片是否成功加载
    if (img.empty()) {
        std::cerr << "错误: 无法读取图片，请检查路径是否正确！" << std::endl;
        return -1;
    }

    // 3. 创建一个名为 "Display" 的窗口，并显示图片
    cv::imshow("Display", img);

    // 4. 等待用户按键 (参数 0 表示无限期等待，直到有按键输入)
    std::cout << "图片已显示，按任意键退出..." << std::endl;
    cv::waitKey(0);

    // 窗口会自动销毁，内存由 cv::Mat 自动管理，无需手动 free
    return 0;
}


int main(int argc, char** argv) {
    // 检查命令行参数
    //if (argc != 2) {
    //    std::cerr << "用法: " << argv[0] << " <图片路径>" << std::endl;
    //    return -1;
    //}
    cv::VideoCapture vc;
    //auto vc = cv::VideoCapture("http://vjs.zencdn.net/v/oceans.mp4");
    cv::Mat img;
    vc.open("http://vjs.zencdn.net/v/oceans.mp4", cv::CAP_ANY);
    while (vc.isOpened()) {
        auto ok = vc.read(img);
        if (ok) {
            // 3. 创建一个名为 "Display" 的窗口，并显示图片
            cv::imshow("Display", img);
        }
        int key = cv::waitKey(30) & 0xff;
        if (key == 'q' || key == 27) {
            break;
        }
    }

    //const char* image_path = "House_1_Wood_Base_Blue.png";//argv[1];

    //// 1. 读取图片 (cv::IMREAD_COLOR 表示以彩色模式读取)
    //cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

    //// 2. 检查图片是否成功加载
    //if (img.empty()) {
    //    std::cerr << "错误: 无法读取图片，请检查路径是否正确！" << std::endl;
    //    return -1;
    //}

    //// 3. 创建一个名为 "Display" 的窗口，并显示图片
    //cv::imshow("Display", img);

    // 4. 等待用户按键 (参数 0 表示无限期等待，直到有按键输入)
    std::cout << "图片已显示，按任意键退出..." << std::endl;
    //cv::waitKey(0);

    // 窗口会自动销毁，内存由 cv::Mat 自动管理，无需手动 free
    return 0;
}