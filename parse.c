#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>

#define FILENAME "1.xml"

int parseHreadElement(xmlDocPtr doc,xmlNodePtr cur)
{
	xmlChar *content;
	
	cur = cur->xmlChildrenNode;
	while(cur != NULL)
	{
		if(!xmlStrcmp(cur->name,(const xmlChar*)"title"))
		{
			content = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
			printf("Tab title = %s\n",content);
			xmlFree(content);
		}
		cur = cur->next;
	}
	return 0;
}

int parseBodyElement(xmlDocPtr doc,xmlNodePtr cur)
{
	xmlChar *content;
	
	cur = cur->xmlChildrenNode;
	while(cur != NULL)
	{
		if(!xmlStrcmp(cur->name,(const xmlChar*)"h1"))
		{
			content = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
			printf("H1 title = %s\n",content);
			xmlFree(content);
		}
		if(!xmlStrcmp(cur->name,(const xmlChar*)"p"))
		{
			content = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
			printf("paragraph content = %s\n",content);
			xmlFree(content);
		}
		cur = cur->next;
	}
	return 0;
}

int parseHtml(const char*fileName)
{
	xmlDocPtr doc;
	xmlNodePtr cur;
	xmlChar *id;

	doc = xmlParseFile(fileName);
	if(doc == NULL)
	{
		printf("ERROR\n");
		return -1;
	}
	cur = xmlDocGetRootElement(doc);
	if(xmlStrcmp(cur->name,(const xmlChar*)"html"))
	{
		printf("%s is not a html file",fileName);
		if(doc != NULL)
		xmlFreeDoc(doc);
		return -1;
	}
	cur = cur->xmlChildrenNode;
	while(cur != NULL)
	{
		if(!xmlStrcmp(cur->name,(const xmlChar*)"head"))
		{
			// = xmlGetProp(cur,(const xmlChar*)
			parseHreadElement(doc,cur);

		}
		else if(!xmlStrcmp(cur->name,(const xmlChar*)"body"))
		{
			parseBodyElement(doc,cur);
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return 0;
}

int main()
{
	parseHtml(FILENAME);
	return 0;
}



