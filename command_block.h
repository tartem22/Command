#ifndef COMMAND_BLOCK_H
#define COMMAND_BLOCK_H

/*!
\file Заголовочный фаил, содержащий описание абстрактного
класса командного блока
*/

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "command.h"


/*!
Абстрактный класс командного блока
*/
class CommandBlock
{
public:
    /*!
    Добавляет комманду в блок
    \param[in] cmd Указатель на команду
    \return Признак успешности добавления команды в блок
    */
    virtual bool add(std::shared_ptr<Command> cmd);
    /// Завершает работу блока
    virtual void release();
    /*!
    Проверяет, является ли блок динамическим
    \return true, если блок динамический, иначе false
    */
    virtual bool isDynamic() = 0;
    /*!
    Проверяет, является ли блок игнорируемым
    \return true, если блок игнорируемый, иначе false
    */
    bool isIgnored();
    /// Делает блок игнорируемым
    void setAsIgnored();

protected:
    /// Перечень команд в блоке
    std::vector<std::shared_ptr<Command>> commands;
    /// Устанавливает таймкод блока
    void setTimeCode();
    /// Выводит команды блока в коммандную строку
    void logToCommandLine();
    /// Выводит команды блока в фаил
    void logToFile();

private:
    /// Класс логера комманд блока в фаил
    class FileLogger
    {
    public:
        /// Класс логера комманд в фаил
        ~FileLogger()
        {
            if (file.is_open())
                file.close();
        }
        /*!
        Открывает фаил, в который осуществляется логгирование
        \param[in] fileName Полное имя файла, в который осуществялется логгирование
        \return true, если фаил успешно открыт для записи, иначе false
        */
        bool open(std::string fileName);
        /// Закрывает фаил, в который осуществляется логгирование
        void close();
        /*!
        Логирует строку в фаил
        \param[in] str Логгируемая строка
        */
        void operator<<(const std::string &str);

    private:
        /// Файловый поток, в который осуществляется логгирование
        std::ofstream file;
    };

    /// Таймкод блока: время добавление первой команды
    std::string timeCode;
    /// Признак игнорируемости блока
    bool isIgnored_ = false;
};

#endif // COMMAND_BLOCK_H
