/****************************************************************************
** Meta object code from reading C++ file 'qqrencode.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../qtqrencode/qqrencode/qqrencode.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qqrencode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QQREncode_t {
    QByteArrayData data[6];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QQREncode_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QQREncode_t qt_meta_stringdata_QQREncode = {
    {
QT_MOC_LITERAL(0, 0, 9), // "QQREncode"
QT_MOC_LITERAL(1, 10, 20), // "ErrorCorrectionLevel"
QT_MOC_LITERAL(2, 31, 3), // "LOW"
QT_MOC_LITERAL(3, 35, 6), // "MEDIUM"
QT_MOC_LITERAL(4, 42, 8), // "QUARTILE"
QT_MOC_LITERAL(5, 51, 4) // "HIGH"

    },
    "QQREncode\0ErrorCorrectionLevel\0LOW\0"
    "MEDIUM\0QUARTILE\0HIGH"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QQREncode[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
       1, 0x0,    4,   18,

 // enum data: key, value
       2, uint(QQREncode::LOW),
       3, uint(QQREncode::MEDIUM),
       4, uint(QQREncode::QUARTILE),
       5, uint(QQREncode::HIGH),

       0        // eod
};

const QMetaObject QQREncode::staticMetaObject = {
    { nullptr, qt_meta_stringdata_QQREncode.data,
      qt_meta_data_QQREncode,  nullptr, nullptr, nullptr}
};

QT_WARNING_POP
QT_END_MOC_NAMESPACE
