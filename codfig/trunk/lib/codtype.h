// File: codtype.h
// decleration of the codtype abstract class
// Copyright (C) 2006 Shaun Bouckaert

#ifndef TRAINMEDITATION_CODTYPE_H
#define TRAINMEDITATION_CODTYPE_H

namespace codfig{
    class AbstractCodType{
    public:
        virtual const string & stringValue() const = 0;
        virtual AbstractCodType & operator= (const char *) = 0;
        virtual AbstractCodType & operator= (const unsigned int) = 0;
        virtual AbstractCodType & operator= (const signed int) = 0;
        virtual AbstractCodType & operator= (const bool) = 0;
        virtual AbstractCodType & operator= (const string &) = 0;
        virtual ~AbstractCodType() = 0;
    };

    template <class T> 
        class CodType : public AbstractCodType{
            public:
                CodType & operator= (const char *);
                CodType & operator= (const unsigned int);
                CodType & operator= (const signed int);
                CodType & operator= (const bool);
                CodType & operator= (const string &);
                CodType & operator= (const T &);

                const string & stringValue() const;

                ~CodType();
            private:
                T * value;
        };
}

#endif
