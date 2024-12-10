# Установка и настройка gRPC на Windows с использованием CMake и vcpkg

## Содержание
1. [Установка CMake](#шаг-1-установка-cmake)
2. [Установка пакетного менеджера vcpkg](#шаг-2-установка-пакетного-менеджера-vcpkg)
3. [Установка gRPC через vcpkg](#шаг-3-установка-grpc-с-помощью-vcpkg)
4. [Добавление protoc в PATH](#шаг-4-добавление-protoc-в-переменную-среды-path)
5. [Создание проекта CMake в Visual Studio](#шаг-5-создание-проекта-cmake-в-visual-studio)
6. [Сборка проекта](#шаг-6-build-проекта-и-создание-исполняемых-файлов-serverexe-и-clientexe)

---

## Шаг 1: Установка CMake

---

## Скачивание CMake

1. Перейдите на официальный сайт CMake:
   [https://cmake.org/download/](https://cmake.org/download/)

2. Выберите версию, подходящую для вашей операционной системы (в нашем случае, выбираем версию для Windows):
   - **Windows**: `cmake-x.x.x-windows-x86_64.msi`

---

## Установка

### Для Windows:
1. Запустите скачанный `.msi` установщик.
2. Следуйте инструкциям мастера установки:
   - Убедитесь, что выбрана опция **Add CMake to the system PATH** для удобного использования CMake из командной строки.
3. После завершения установки откройте командную строку и выполните команду:
   ```sh
   cmake --version
   ```

---

## Установка пакета CMake C++ для Windows
1. Переходим в Пуск, в строке поиска пишем **Visual Studio Installer**, далее запускаем инсталлятор.
2. В окне инсталлятора находим нужную нам версию Visual Studio (если у вас установлены разные версии) и нажимаем на кнопку **Изменить**.
3. В открывшимся окне переходим в раздел **Отдельные компоненты** и в строку поиска пишем **CMake C++ для Windows**.
4. В результатах будет компонент с именем **Средства CMake C++ для Windows**, для установки нажимаем на галочку слева от компонента и соглашаемся с установкой.
---

## Шаг 2: Установка пакетного менеджера vcpkg

---

## Клонирование репозитория vcpkg

1. Создаем папку на диске (к примеру, создадим папку по пути `E:\v2`), переходим в нее и делаем клонирование репозитория командой:
   ```sh
   git clone https://github.com/microsoft/vcpkg.git
   ```

2. Теперь, когда вы клонировали репозиторий vcpkg, перейдите к vcpkg каталогу и выполните скрипт начальной загрузки:
   ```sh
   cd vcpkg
   ```
   ```sh
   bootstrap-vcpkg.bat
   ```

3. После этого можно проверить корректность установки, для этого пишем:
   ```sh
   vcpkg --version
   ```
   В случае корректной установки, в консоль будет выведено `vcpkg package management program version 2024-11-12-eb492805e92a2c14a230f5c3deb3e89f6771c321`, где `2024-11-12-eb492805e92a2c14a230f5c3deb3e89f6771c321`- комбинация из даты сборки программы и хэш коммита в репозитории vcpkg

---

## Шаг 3: Установка gRPC с помощью vcpkg

---

## Установка необходимых библиотек

**!!! Важное уточнение !!! После выполнения первой команды ниже, возможно скачается и protobuf, однозначного ответа на этот вопрос нет, у многих скачивало сразу, выполняем команды по очереди и смотрим, что выводится в консоль**


1. Установите gRPC для архитектуры x64-windows:
   ```sh
   vcpkg install grpc:x64-windows
   ```

2. Установите protobuf (протокол сериализации данных, используемый в gRPC):
   ```sh
   vcpkg install protobuf protobuf:x64-windows
   ```

3. Добавьте поддержку zlib (сжатие данных) для protobuf:
   ```sh
   vcpkg install protobuf[zlib] protobuf[zlib]:x64-windows
   ```

---

## Интеграция vcpkg с вашей системой

4. Добавьте поддержку zlib (сжатие данных) для protobuf:
   ```sh
   vcpkg integrate install
   ```
После успешной интеграции vcpkg автоматически будет находить библиотеки, установленные через него, и добавлять их в проекты CMake.

---

## Шаг 4: Добавление protoc в переменную среды PATH

---

1. Нажимаем комбинацию клавиш `Win+S`, в строке поиска пишем `Изменение системных переменных среды`, нажимаем Enter. Переходим в раздел `Переменные среды`, в окне `Системные переменные` находим переменную `PATH`, нажимаем на нее и выбираем `Изменить`. В появившимся окне выбираем пункт и вставляем путь к исполняемому файлу protoc.exe (в моем случае, путь будет вот таким: `E:\v2\vcpkg\packages\protobuf_x64-windows\tools\protobuf`).

---

## Шаг 5: Создание проекта CMake в Visual Studio

---

## Создание проекта

1. Откройте **Visual Studio**.

2. Выберите пункт меню **Создание проекта**.

3. В появившемся окне создания нового проекта выполните следующие шаги:
   - Найдите и выберите шаблон **Проект CMake**.
   - Нажмите **Далее**.

4. Укажите:
   - Имя проекта (например, **gRPC**).
   - Путь для сохранения проекта.
   - Нажмите **Создать**.

---

## Создание proto-файла

1. В корне проекта создаем папку **proto**.

2. В этой папке создаем файл, к примеру, **math_operations.proto**.

3. Пример файла **math_operations.proto**:
   ```proto
   syntax = "proto3";

   package math;

   service MathService {
    rpc Add (Parm2Request) returns (Parm2Result);
    rpc Sub (Parm2Request) returns (Parm2Result);
    rpc Mul (Parm2Request) returns (Parm2Result);
    rpc Div (Parm2Request) returns (Parm2Result);
    rpc Pow (Parm2Request) returns (Parm2Result);
   }

   message Parm2Request {
    double x = 1;
    double y = 2;
   }

   message Parm2Result {
    double z = 1;
    string error = 2;
   }
   ```

4. В корневой папке проекта открываем консоль и пишем туда команды:
   ```sh
   protoc -I=proto --cpp_out=proto proto/math_operations.proto
   ```

   Результат: Создается файл math_operations.pb.h и math_operations.pb.cc. Эти файлы содержат:
     - Классы для всех сообщений, определенных в math_operations.proto.
     - Методы для сериализации (в двоичный формат) и десериализации.


   ```sh
   protoc -I=proto --grpc_out=proto --plugin=protoc-gen-grpc="E:\v2\vcpkg\packages\grpc_x64-windows\tools\grpc\grpc_cpp_plugin.exe" proto/math_operations.proto
   ```

   Результат: Создается файл math_operations.grpc.pb.h и math_operations.grpc.pb.cc. Эти файлы содержат:
     - Код для клиентской и серверной логики (stub и skeleton) для вызова удаленных процедур (RPC), определенных в .proto файле.
     - gRPC интерфейсы, которые можно использовать для создания серверов и клиентов.

---

## Создание сервера и клиента

1. В корне проекта создаем папку **src**.

2. В этой папке создаем два файла: **server.cpp** и **client.cpp**.

3. Пишем логику сервера и клиента, с учетом нашего proto-файла:

   Server.cpp
   ```cpp
   #include <grpcpp/grpcpp.h>
   #include "math_operations.grpc.pb.h"
   #include <cmath>
   #include <iostream>

   class MathServiceImpl final : public math::MathService::Service {
   public:
    grpc::Status Add(grpc::ServerContext* context, const math::Parm2Request* request,
        math::Parm2Result* response) override {
        response->set_z(request->x() + request->y());
        return grpc::Status::OK;
    }

    grpc::Status Sub(grpc::ServerContext* context, const math::Parm2Request* request,
        math::Parm2Result* response) override {
        response->set_z(request->x() - request->y());
        return grpc::Status::OK;
    }

    grpc::Status Mul(grpc::ServerContext* context, const math::Parm2Request* request,
        math::Parm2Result* response) override {
        response->set_z(request->x() * request->y());
        return grpc::Status::OK;
    }

    grpc::Status Div(grpc::ServerContext* context, const math::Parm2Request* request,
        math::Parm2Result* response) override {
        if (request->y() == 0) {
            response->set_error("Division by zero is not allowed.");
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Division by zero");
        }
        response->set_z(request->x() / request->y());
        return grpc::Status::OK;
    }

    grpc::Status Pow(grpc::ServerContext* context, const math::Parm2Request* request,
        math::Parm2Result* response) override {
        response->set_z(pow(request->x(), request->y()));
        return grpc::Status::OK;
    }
   };

   void RunServer() {
    std::string server_address("0.0.0.0:50051");
    MathServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
   }

   int main() {
    RunServer();
    return 0;
   }
   ```

   Client.cpp
   ```cpp
   #include <grpcpp/grpcpp.h>
   #include "math_operations.grpc.pb.h"
   #include <iostream>
   #include <future>

   using grpc::Channel;
   using grpc::ClientContext;
   using grpc::Status;
   using math::MathService;
   using math::Parm2Request;
   using math::Parm2Result;

   class MathClient {
   public:
    MathClient(std::shared_ptr<Channel> channel)
        : stub_(MathService::NewStub(channel)) {
   }

    void Add(double x, double y) {
        Parm2Request request;
        request.set_x(x);
        request.set_y(y);

        Parm2Result response;
        ClientContext context;

        Status status = stub_->Add(&context, request, &response);
        if (status.ok()) {
            std::cout << "Addition result: " << response.z() << std::endl;
        }
        else {
            std::cout << "Error: " << response.error() << std::endl;
        }
    }

    void Subtract(double x, double y) {
        Parm2Request request;
        request.set_x(x);
        request.set_y(y);

        Parm2Result response;
        ClientContext context;

        Status status = stub_->Sub(&context, request, &response);
        if (status.ok()) {
            std::cout << "Subtraction result: " << response.z() << std::endl;
        }
        else {
            std::cout << "Error: " << response.error() << std::endl;
        }
    }

    void Multiply(double x, double y) {
        Parm2Request request;
        request.set_x(x);
        request.set_y(y);

        Parm2Result response;
        ClientContext context;

        Status status = stub_->Mul(&context, request, &response);
        if (status.ok()) {
            std::cout << "Multiplication result: " << response.z() << std::endl;
        }
        else {
            std::cout << "Error: " << response.error() << std::endl;
        }
    }

    void Divide(double x, double y) {
        Parm2Request request;
        request.set_x(x);
        request.set_y(y);

        Parm2Result response;
        ClientContext context;

        Status status = stub_->Div(&context, request, &response);
        if (status.ok()) {
            std::cout << "Division result: " << response.z() << std::endl;
        }
        else {
            std::cout << "Error: " << status.error_message() << std::endl;
        }
    }


    void Power(double x, double y) {
        Parm2Request request;
        request.set_x(x);
        request.set_y(y);

        Parm2Result response;
        ClientContext context;

        Status status = stub_->Pow(&context, request, &response);
        if (status.ok()) {
            std::cout << "Power result: " << response.z() << std::endl;
        }
        else {
            std::cout << "Error: " << response.error() << std::endl;
        }
    }

    std::future<void> MultiplyAsync(double x, double y) {
        return std::async(std::launch::async, [this, x, y]() {
            Parm2Request request;
            request.set_x(x);
            request.set_y(y);

            Parm2Result response;
            ClientContext context;

            Status status = stub_->Mul(&context, request, &response);
            if (status.ok()) {
                std::cout << "Multiplication result (async): " << response.z() << std::endl;
            }
            else {
                std::cout << "Error: " << response.error() << std::endl;
            }
            });
    }

    private:
      std::unique_ptr<MathService::Stub> stub_;
    };

   int main() {
     MathClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

     client.Add(3, 4);
     client.Subtract(10, 5);
     client.Multiply(6, 7);
     auto multiplyFuture = client.MultiplyAsync(6, 7);
     multiplyFuture.get();
     client.Divide(10, 2);
     client.Divide(10, 0);
     client.Power(2, 3);

     std::cout << "Press Enter to exit...";
     std::cin.get();

     return 0;
    }
   ```

---

## Настройка CMakeLists.txt

1. В корневой директории проекта Visual Studio создаст файл `CMakeLists.txt`.  
   Откройте его и добавьте или отредактируйте следующие строки:

   ```cmake
   cmake_minimum_required(VERSION 3.15)

   project(gRPC)

   set(re2_DIR "E:/v2/vcpkg/installed/x64-windows/share/re2")
   set(absl_DIR "E:/v2/vcpkg/installed/x64-windows/share/absl")
   set(gRPC_DIR "E:/v2/vcpkg/installed/x64-windows/share/grpc")
   set(utf8_range_DIR "E:/v2/vcpkg/installed/x64-windows/share/utf8_range")
   set(Protobuf_DIR "E:/v2/vcpkg/installed/x64-windows/share/protobuf")
   set(ZLIB_INCLUDE_DIR "E:/v2/vcpkg/installed/x64-windows/include")
   set(ZLIB_LIBRARY "E:/v2/vcpkg/installed/x64-windows/lib/zlib.lib")
   set(c-ares_DIR "E:/v2/vcpkg/installed/x64-windows/share/c-ares")
   set(OPENSSL_ROOT_DIR "E:/v2/vcpkg/installed/x64-windows")


   find_package(gRPC CONFIG REQUIRED)
   find_package(Protobuf CONFIG REQUIRED)
   find_package(OpenSSL REQUIRED)
   find_package(c-ares CONFIG REQUIRED)

   if(NOT TARGET ZLIB::ZLIB)
      find_path(ZLIB_INCLUDE_DIR NAMES zlib.h PATHS ${ZLIB_INCLUDE_DIR})
      find_library(ZLIB_LIBRARY NAMES zlib PATHS ${ZLIB_LIBRARY})
      add_library(ZLIB::ZLIB STATIC IMPORTED)
      set_target_properties(ZLIB::ZLIB PROPERTIES
         INTERFACE_INCLUDE_DIRECTORIES ${ZLIB_INCLUDE_DIR}
         INTERFACE_LINK_LIBRARIES ${ZLIB_LIBRARY}
      )
   endif()

   include_directories(proto)

   add_executable(server src/server.cpp proto/math_operations.grpc.pb.cc proto/math_operations.pb.cc)
   add_executable(client src/client.cpp proto/math_operations.grpc.pb.cc proto/math_operations.pb.cc)

   target_link_libraries(server PRIVATE gRPC::grpc++ gRPC::grpc++_reflection protobuf::libprotobuf ZLIB::ZLIB OpenSSL::SSL OpenSSL::Crypto)
   target_link_libraries(client PRIVATE gRPC::grpc++ gRPC::grpc++_reflection protobuf::libprotobuf ZLIB::ZLIB OpenSSL::SSL OpenSSL::Crypto)
   ```

---

## Шаг 6: Build проекта и создание исполняемых файлов server.exe и client.exe

---

1. В корне проекта создаем папку **build**.

2. Переходим в созданную папку, открываем консоль и прописываем следующие команды:
   ```sh
   cmake .. -DCMAKE_TOOLCHAIN_FILE=E:/v2/vcpkg/scripts/buildsystems/vcpkg.cmake
   ```
   ```sh
   cmake --build . --config Release
   ```
   Первая команда настраивает проект и готовит сборочную систему, интегрируя зависимости через vcpkg.

   Вторая команда компилирует проект в указанной конфигурации (Release), создавая итоговые .exe файлы.


3. Переходим в папку **Release**, которая создалась в папке **build** и видим два файла - `server.exe` и `client.exe`. Запускаем вначале сервер, потом клиент.