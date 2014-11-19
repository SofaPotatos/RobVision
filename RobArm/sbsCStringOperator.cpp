#include "sbsCStringOperator.h"

/*******************************************************************************
* Constructor & Destructor
********************************************************************************/

sbsCStringOperator::sbsCStringOperator(void)
{
}

sbsCStringOperator::~sbsCStringOperator(void)
{
}

/*******************************************************************************
* Public Method
********************************************************************************/

string sbsCStringOperator::stringBetween(string orgStr, string startstr, string endstr)
{
    string temp = stringBefore(orgStr,endstr);
    return stringAfter(temp,startstr);
}

int sbsCStringOperator::findString(string orgStr, string str)
{
	return orgStr.find(str);
}

string sbsCStringOperator::stringBefore(string orgStr, string str)
{
	string emptystring;
	int i = findString(orgStr,str);
	if (i<=0)
	{
		return emptystring;
	}
    return orgStr.erase(i, orgStr.length());
}

string sbsCStringOperator::stringAfter(string orgStr, string str)
{
	string emptystring;
	int i = findString(orgStr,str);
	if (i<0)
	{
		return emptystring;
	}

	return orgStr.erase(0,i+1);
}

vector<string> sbsCStringOperator::stringTrimming(string str, string sep)
{
	vector<string> strs;
	strs.reserve(10);
	while (str.length()>0)
	{
		string strpart = stringBefore(str,sep);

		if (strpart.length()>0)
		{
			strs.push_back(strpart);
			str = stringAfter(str,sep);
		}
		else if (strpart.length()==0)
		{
			strs.push_back(str);
			break;
		}
	}
	return strs;
}

double sbsCStringOperator::stringToDouble(string v)
{
    char buffer[256];
    v.copy(buffer,v.length(),0);
	return atof(buffer);
}
