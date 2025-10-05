#pragma once

#include <iostream>
#include <string>
#include <QListWidget>

class load_save
{
private:
    std::string filename;
public:
    load_save(std::string filename);
    ~load_save() = default;

    bool save();
    bool load();
};