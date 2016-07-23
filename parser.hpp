#ifndef PARSER_HPP
#define PARSER_HPP

#endif // PARSER_HPP
#include <QRegExp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <QtDebug>
#include <QUrl>
#include "uriCodec.cpp"
#include <QByteArray>



namespace parser {

using namespace std;
using namespace boost;
QRegExp expression;
QStringList qualityLinks;
QString html;
string getContent(const char* value){
    string temp(value);


    return temp;
}

string videoSpecification(const char* value){
    QRegExp expression;
    QStringList qualityLinks;
    QString html(value);
    string baseString = getContent(value);
    //    url_encoded_fmt_stream_map bis zum nächsten &
    size_t startPos = baseString.find("url_encoded_fmt_stream_map");
    // 27 ist the length of 'url_encoded_fmt_stream_map='
    startPos += 27;
    string searchString = baseString.substr(startPos);
    size_t endPos = searchString.find("&");
    const string middleString = baseString.substr(startPos, endPos);


    QString qStr = QString::fromStdString(middleString);

    //    cout << " "<< endl;
    //    cout << middleString << endl;
//    expression = QRegExp("\"url_encoded_fmt_stream_map\": \"(.*)\"");
//    expression.setMinimal(true);


//    qDebug() << qStr;


//    if (expression.indexIn(html)!=-1 && expression.cap(1) != "")
//    {
//        cout << "so !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<< endl;
//        qualityLinks << expression.cap(1).split(",");
//        cout << qualityLinks.size() << "in QList" << endl;

//    }

//    cout << qualityLinks.size() << "in QList" << endl;
//    for (int i = 0; i < qualityLinks.size(); ++i)
//          cout << qualityLinks.at(i).toLocal8Bit().constData() << endl;

//    QUrl url(qStr);


    string yip = url::UriDecode(middleString);
    cout << yip << endl;








    return "0";
}

}

