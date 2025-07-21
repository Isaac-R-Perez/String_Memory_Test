#include <cstdint>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

/*
    These macros work here, but I'll probably need to make them functions in an actual implementation...

    Okay, I am able to use the text struct to write and grab strings from directly in any memory!!

    let's see if it works with inputing strings

    Got input working and I got text structures being written to memory and read from memory!
    I don't need the macros.
    
    HOWEVER, my implementation here causes the memory pointer to iterate automatically based on the text structs being written to memory.
    A real application would have to keep track of the original memory pointer and use a separate pointer to track where new text
    structs can be written to in memory. Very important.
    
    The WhereToWriteText pointer handles this perfectly!

    Oh, maybe a uint64_t is too much for this?
    a uint32_t can count up to around 4 billion so probably more than enough...


*/

#define string_size(arr) (sizeof(arr) - 1)

#define text_size(txt) (string_size(txt) + sizeof(uint64_t))

const int MAX_STRING_CHARS = 1024;
const int STRINGS_TO_TEST = 3;
const int ARENA_SIZE = STRINGS_TO_TEST * MAX_STRING_CHARS * 2;



//a "text" structure holds how many characters are in the string and a pointer to the first character in memory
struct text
{
    uint64_t Count;
    void* Data;
};


void WriteStringToMemory(void* Destination, uint64_t Count, const char* String)
{
    void* DestCpy = Destination;
    
    //write count into memory
    *((uint64_t*)DestCpy) = Count;

    //move destination past the count
    DestCpy = (uint64_t*)DestCpy + 1;
    
    //cast pointer to a char* for writing string
    char* Write = (char*)DestCpy;

    for(uint64_t i = 0; i < Count; i++)
    {
        *Write++ = String[i];
    }
}


void PrintMessage(text* msg)
{
    char* character = (char*)msg->Data;
    for(int i = 0; i < msg->Count; i++)
    {
        std::cout << *character++;
    }
    std::cout << '\n';
}

//jumps Memory pointer ahead by the given string (a real implementation wouldn't do this???)
void* GetMessage(void* Memory, text* MessageToFill)
{
    char buffer[MAX_STRING_CHARS]{};
    gets_s(buffer, MAX_STRING_CHARS);

    uint64_t length = strlen(buffer);
    WriteStringToMemory(Memory, length, buffer);

    MessageToFill->Count = length;
    
    //move memory pointer up BEFORE pointing Data at it
    Memory = ((uint64_t*)Memory + 1);

    MessageToFill->Data = Memory;

    Memory = ((char*)Memory + (sizeof(char) * length));

    return Memory;

}

int main()
{

    std::cout << "Please enter " << STRINGS_TO_TEST << " strings. Check their memory being written in your debugger!\n";

    void* Memory = malloc( ARENA_SIZE * sizeof(char) );

    void* WhereToWriteText = Memory;

    text Tester[STRINGS_TO_TEST];

    for(int i = 0; i < STRINGS_TO_TEST; i++)
    {
        WhereToWriteText = GetMessage(WhereToWriteText, &Tester[i]);
    }

    std::cout << '\n';
    for(int i = 0; i < STRINGS_TO_TEST; i++)
    {
        PrintMessage(&Tester[i]);
    }

	char a;
	std::cin >> a;
    


    return 0;
}