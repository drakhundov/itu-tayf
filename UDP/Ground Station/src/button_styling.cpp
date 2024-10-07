#include "button_styling.h"

void UpdBtnStyle(QPushButton *btn, QString param, QString styleVal)
{
    QString finStyle = btn->styleSheet();
    QString newStyle = param + ":" + styleVal + ";";
    int pos;
    if ((pos = finStyle.indexOf(param)) != -1)
    {
        int endPos = finStyle.indexOf(";", pos);
        if (endPos != -1)
        {
            finStyle.replace(pos, endPos - pos + 1, newStyle);
        }
        else
        {
            finStyle.replace(pos, finStyle.length() - pos, newStyle);
        }
    }
    else
    {
        if (!finStyle.isEmpty() && !finStyle.endsWith(";"))
        {
            finStyle.append(";");
        }
        finStyle.append(newStyle);
    }
    btn->setStyleSheet(finStyle);
}