#ifndef SFILE_H
#define SFILE_H

class QString;


class SFile
{
public:
    SFile(int inPosition, QString inName);

    int position;
    QString name;
};

#endif // SFILE_H
