build	:	main.o Bitmap.o ContoursTools.o ListTable.o MyLinkedList.o
		g++ -o build main.o Bitmap.o ContoursTools.o ListTable.o MyLinkedList.o
main.o	:	main.cpp ContoursTools.h
		g++ -g -c main.cpp
Bitmap.o	:	Bitmap.h Bitmap.cpp
		g++ -g -c Bitmap.cpp
ContoursTools.o	:	ContoursTools.h ContoursTools.cpp
		g++ -g -c ContoursTools.cpp
ListTable.o	:	ListTable.h ListTable.cpp
		g++ -g -c ListTable.cpp
MyLinkedList.o	:	MyLinkedList.h MyLinkedList.cpp
		g++ -g -c MyLinkedList.cpp
clean:
		rm main.o Bitmap.o ContoursTools.o ListTable.o MyLinkedList.o