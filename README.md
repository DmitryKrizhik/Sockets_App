# *__Оглавление__*
- *Описание программы*

- *Запуск программы*

- *Проверка результата работы программы*

___
## *__Описание проекта__*
В данной программе реализуется клиент-серверное приложение под Linux, где 

*__Клиент__* - программа, запускаемая из консоли. *Клиент* передаёт содержимое текстового файла через ТСР.

*__Сервер__* - демон, корректно завершающийся по сигналам SIGTERM и SIGHUP. *Сервер* принимает содержимое текстового файла, полученного от *клиента* и сохраняет его в новый файл.

## *__Запуск проекта__*
- Скачиваем репозиторий:
 ```
 $ git clone https://github.com/DmitryKrizhik/Sockets_App
 $ cd Sockets_App
 ```
 - Запускаем работу сервера:
 ```
 $ g++ server.cpp -o server
 $ ./server
 ```
 - Запускаем работу клиента:
 ```
 $ g++ client.cpp /client
 $ ./client TestText.txt
 ```
 - *__Завершить работу сервера можно следующим образом:__*
 ```
 $ netstat -pnltu 
 ```
 - Получаем вывод:
 ```
 Proto   Recv-Q Send-Q Local Address Foreign    Address State        PID/Program name                   
tcp          0      0 0.0.0.0:8080               0.0.0.0:*          LISTEN      24184/./server
 ```
 - Из этого вывода мы видим, что PID нашего сервера = 24184. Завершаем работу сервера одним из следующих способов:
  1)
 ```
 $ kill -1 24184
 ```
 - Получаем вывод: 
 ```
 Received signal 1, shutting down server...
 ```
 2)
 ```
 $ kill -15 24184
 ```
 - Получаем вывод: 
  ```
 Received signal 15, shutting down server...
 ```
 
 ## *__Проверка результата работы программы__*
 - Проверяем результат работы программы следующим образом:
 ```
 $ ls
 ```
 - Получаем вывод: 
 ```
 2023-05-10_16-31-40.txt  client  client.cpp  server  server.cpp  TestText.txt
 ```
 - Открываем текстовый файл, созданный сервером:
 ```
  $ open 2023-05-10_16-31-40.txt
 ```
 - Получаем содержимое файла: 
 ```
 Linux is an open-source operating system that is widely used in servers, supercomputers, and mobile devices. 
 It was first released in 1991 by Linus Torvalds and has since grown into a powerful and flexible platform. 
 Linux is known for its stability, security, and customization options, making it a popular choice for developers and tech enthusiasts. 
 With its vast library of software and tools, Linux offers endless possibilities for those looking to create and innovate.
 ```
 
 
 
 
 
 
 
 
 
 
 
 
 
