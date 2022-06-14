#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

/*!
\file Заголовочный фаил с описанием класса обработчика команд

Данный фаил содержит в себе описание класса обработчика команд
*/

#include <memory>
#include <stack>
#include "command_block.h"

/*!
Класс обработчика команд
*/
class CommandHandler
{
public:
    /*! 
    Конструктор класса обработчика команд
    \param[in] size Размер статического блока команд
    */
    CommandHandler(int size) : staticBlockSize(size){}
    /*!
    Обрабатывает поток команд и управляющих символов, 
    представленных в виде строк
    \param[in] cmd Команда или управляющий символ 
    */
    void handle(std::string cmd);
    
private:
    /// Размер статического блока
    int staticBlockSize = 0;
    /// Текущий командный блок
    std::shared_ptr<CommandBlock> currBlock = nullptr;
    /// Стек командных блоков
    std::stack<std::shared_ptr<CommandBlock>> blocks;

    /*! 
    Добавляет новый динамический командный блок в стек
    и делает новый блок текущим
    */
    void createNewDynamicBlock();
    /*! 
    Добавляет новый статический командный блок в стек
    и делает новый блок текущим
    */
    void createNewStaticBlock();
    /*!
    Удаляет текущий блок из стека и назначает предыдущий командный
    текущим, в случае если стек не пуст
    */
    void releaseCurrentBlock();
};

#endif // COMMAND_HANDLER_H
