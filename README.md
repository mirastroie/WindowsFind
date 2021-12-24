# WindowsFind

A Win32 Console application that mimics minimal [find](https://man7.org/linux/man-pages/man1/find.1.html) functionality. The core component of the application is a C++ RAII wrapper over Win32 API FindFirstFileW/FindNextFile/FindClose.
I used the singleton design pattern and namespaces to implement, manage and group the functionalities. I made use of C++ modern features, particularly unique_ptr smart pointer and lambda expressions.
