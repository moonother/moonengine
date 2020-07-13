#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader_s.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
#if 0
//顶点着色器源代码
const char*vertexShaderSource = "#version 330 core\n"  
"layout (location = 0) in vec3 aPos;\n" //位置变量的属性位置为0
"out vec4 vertexColor;\n" // 为片段着色器指定一个颜色输出
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0);"
"vertexColor = vec4(1.0, 1.0, 0.0, 1.0);\n" // 把输出变量设置为暗红色
"}\n\0";
//片段着色器源代码

const char* FragColorSource = "#version 330 core\n"
"out vec4 FragColor;\n"

//"in vec4 vertexColor;\n" // 从顶点着色器传来的输入变量（名称相同、类型相同）
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
//"FragColor = vertexColor;\n"
"FragColor = ourColor;\n"
"}\n\0";

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"  //位置变量的属性位置为0
"layout (location = 1) in vec3 aColor;\n"// 颜色变量的属性位置值为 1
"out vec3 ourColor;\n" // 向片段着色器输出一个颜色
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"ourColor = aColor;\n"
"}\n\0";
const char* FragColorSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(ourColor, 1.0);\n"
"}\n\0";
#endif
int main()
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int texture1;
    unsigned int texture2;
    int vertexShader;
    int fragmentShader;
    int shaderProgram;
    int success;
    int width, height, nrChannels;
    char infoLog[512];
    int vertexColorLocation;
    float timeValue;
    float greenValue;
    float xyset;
    float borderColor;
   // unsigned int VBO, VAO;
    /*
    float vertices[] = {  //顶点坐标
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };
    
    
    float vertices[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
    };
     */
    unsigned int indices[] = { // 注意索引从0开始! 
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
   
    float vertices[] = {//矩形带纹理坐标
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    //--------------creatwindow------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glViewport(0, 0, 800, 600);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    Shader ourShader("3.3.shader.vs", "3.3.shader.fs");
    glGenVertexArrays(1, &VAO); //创建一个VAO对象
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);  //创建一个VBO对象


    glBindVertexArray(VAO); //把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用

    glBindBuffer(GL_ARRAY_BUFFER, VBO); //把VBO对象绑定到GL_ARRAY_BUFFER上
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  //把定义的顶点数据复制到缓冲的内存中
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
#if 0
    vertexShader = glCreateShader(GL_VERTEX_SHADER); //创建顶点着色器

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //把源码以字符串形式附加到着色器对象上

    glCompileShader(vertexShader);  //编译顶点着色器


    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //创建片段着色器

    glShaderSource(fragmentShader, 1, &FragColorSource, NULL); //把源码以字符串形式附加到着色器上

    glCompileShader(fragmentShader); //编译片段着色器


    shaderProgram = glCreateProgram(); //创建一个着色器程序

    glAttachShader(shaderProgram, vertexShader); //把顶点着色器附加到程序上
    glAttachShader(shaderProgram, fragmentShader); //把片段着色器附加到程序上
    glLinkProgram(shaderProgram);  //链接顶点着色器和片段着色器

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); //删除着色器对象

#endif
     //设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    /*
    第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
    第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
    第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
    下个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。
    第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个float之后，我们把步长设置为3 * sizeof(float)。要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，我们在后面会看到更多的例子（译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节）。
    最后一个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。
    */
    
    
   // glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(0); //启用顶点属性

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //glBindVertexArray(0);

    //someOpenGLFunctionThatDrawsOurTriangle();
    //纹理1
    //----------------------------------------------------------
    //borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    stbi_set_flip_vertically_on_load(true);//翻转图像Y轴
    unsigned char* data1 = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    if (data1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);//注意GL_RGB这个参数！必须根据具体图像是否有alpha通道来选择参数！
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture1" << std::endl;
    }
    stbi_image_free(data1);


    //纹理2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    
    unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 4);//注意，此函数的第四个参数为返回通道数,可能需要与图片通道数保持一致，若为0可能会报错
    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture2" << std::endl;
    }

    stbi_image_free(data2);
    //----------------------------------------------------------
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    ourShader.use(); // 别忘记在激活着色器前先设置uniform！
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // 手动设置
    ourShader.setInt("texture2", 1); // 或者使用着色器类设置

    while (!glfwWindowShouldClose(window))
    {

        processInput(window);
        //渲染
        //清除颜色缓冲
        glClearColor(0.3f, 0.4f, 0.3f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT); //不能放在glDrawArrays的后面，否则会提前清空着色器的缓冲
#if 0
        timeValue = glfwGetTime();//获取运行的时间
        greenValue = (sin(timeValue) / 2.0f) + 0.5f;//使用sin函数改变颜色
        vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");//查询uniform ourColor的位置值
#endif   

        timeValue = glfwGetTime();
        xyset = sin(timeValue*5)*0.5;


       //纹理1
        glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, texture1);
        //纹理2
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        
        ourShader.use();
        //ourShader.setFloat("xOffset1", xset);
        ourShader.setFloat("xyOffset", xyset);
        ourShader.setFloat("cvalue", xyset);
        glBindVertexArray(VAO);
        //ourShader.setFloat("someUniform", 1.0f);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
       // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}