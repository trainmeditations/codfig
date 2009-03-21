// File: codtype.h
// decleration of the codtype abstract class
// Copyright (C) 2006 Shaun Bouckaert

#ifndef TRAINMEDITATION_CODTYPE_H
#define TRAINMEDITATION_CODTYPE_H

namespace codfig{
    class cod_type{
    public:
        virtual string stringValue() const = 0;
        virtual string valueType() const = 0;
    private:
    };
}

#endif