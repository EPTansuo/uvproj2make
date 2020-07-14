#include "parse.h"
int parseFilesElement(xmlDocPtr doc,xmlNodePtr node)
{
	xmlChar *content;
	xmlNodePtr node_pre;
	node = node->xmlChildrenNode;
	while(node != NULL)
	{
		if(!xmlStrcmp(node->name,(const xmlChar*)"File"))
		{
			node_pre = node;
			node = node->xmlChildrenNode;
			while (node != NULL )
			{
				if(!xmlStrcmp(node->name,(const xmlChar*)"FileName"))
				{
					content = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
					printf("FileName = %s\n",content);
					xmlFree(content);
				}
				else if(!xmlStrcmp(node->name,(const xmlChar*)"FileType"))
				{
					content = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
					printf("FileType = %s\n",content);
					xmlFree(content);
				}
				else if(!xmlStrcmp(node->name,(const xmlChar*)"FilePath"))
				{
					content = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
					printf("FilePath = %s\n",content);
					xmlFree(content);
				}
				node = node->next;
			}
			node = node_pre;
		}
		node = node->next;
	}
	return 0;
}

int parseTargetOptionElement(xmlDocPtr doc,xmlNodePtr node)
{
	xmlChar *content;
	xmlNodePtr node_pre;
	node = node->xmlChildrenNode;
	while(node != NULL)
	{
		if(!xmlStrcmp(node->name,(const xmlChar*)"TargetCommonOption"))
		{
			node_pre = node;
			node = node->xmlChildrenNode;
			while (node != NULL )
			{
				if(!xmlStrcmp(node->name,(const xmlChar*)"Device"))
				{
					content = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
					printf("Device = %s\n",content);
					xmlFree(content);
				}
				else if(!xmlStrcmp(node->name,(const xmlChar*)"Vendor"))
				{
					content = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
					printf("Vendor = %s\n",content);
					xmlFree(content);
				}
				else if(!xmlStrcmp(node->name,(const xmlChar*)"Cpu"))
				{
					content = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
					printf("Cpu = %s\n",content);
					xmlFree(content);
				}
				node = node->next;
			}
			node = node_pre;
		}
		node = node->next;
	}
	return 0;
}

int parseGroupsElement(xmlDocPtr doc,xmlNodePtr node)
{
	xmlNodePtr node_pre;
	xmlChar *content;
	node = node->xmlChildrenNode;
	while(node != NULL)
	{
		if(!xmlStrcmp(node->name,(const xmlChar*)"Group"))
		{
			node_pre = node;
			node = node->xmlChildrenNode;
			while(node != NULL)
			{
				if(!xmlStrcmp(node->name,(const xmlChar*)"GroupName"))
				{
					content = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
					printf("GroupName = %s\n",content);
					xmlFree(content);
				}
				else if(!xmlStrcmp(node->name,(const xmlChar*)"Files"))
				{
					parseFilesElement(doc,node);
				}
				node = node->next;
			}
			node = node_pre;
		}
		node = node->next;
	}
	return 0;
}


int parseTargetsElement(xmlDocPtr doc,xmlNodePtr node)
{
	xmlNodePtr node_pre;
	xmlChar *content;
	node = node->xmlChildrenNode;
	while(node != NULL)
	{
		if(!xmlStrcmp(node->name,(const xmlChar*)"Target"))
		{
			node_pre = node;
			node = node->xmlChildrenNode;
			while (node != NULL)
			{
				if(!xmlStrcmp(node->name,(const xmlChar*)"TargetName"))
				{
					content = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
					printf("TargetName = %s\n",content);
					xmlFree(content);
				}
				else if(!xmlStrcmp(node->name,(const xmlChar*)"ToolsetNumber"))
				{
					content = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
					printf("ToolsetNumber = %s\n",content);
					xmlFree(content);
				}
				else if(!xmlStrcmp(node->name,(const xmlChar*)"ToolsetName"))
				{
					content = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
					printf("ToolsetName = %s\n",content);
					xmlFree(content);
				}
				else if(!xmlStrcmp(node->name,(const xmlChar*)"TargetOption"))
				{
					parseTargetOptionElement(doc,node);
				}
				else if(!xmlStrcmp(node->name,(const xmlChar*)"Groups"))
				{
					parseGroupsElement(doc,node);
				}
				node = node->next;
			}
			node = node_pre;
		}
		node = node->next;
	}
	return 0;
}


int parseUvproj(const char*fileName)
{
	xmlDocPtr doc;
	xmlNodePtr node;
	xmlChar *content;
	doc = xmlParseFile(fileName);
	if(doc == NULL)
	{
		printf("ERROR\n");
		return -1;
	}
	node = xmlDocGetRootElement(doc);
	if(xmlStrcmp(node->name,(const xmlChar*)"Project"))
	{
		printf("%s is not a .uvproj(x) file",fileName);
		if(doc != NULL)
		xmlFreeDoc(doc);
		return -1;
	}
	node = node->xmlChildrenNode;
	while(node != NULL)
	{
		if(!xmlStrcmp(node->name,(const xmlChar*)"SchemaVersion"))
		{
			content = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
			printf("SchemaVersion = %s\n",content);
			xmlFree(content);
		}
		else if(!xmlStrcmp(node->name,(const xmlChar*)"Header"))
		{
			content = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
			printf("Header = %s\n",content);
			xmlFree(content);
		}
		else if(!xmlStrcmp(node->name,(const xmlChar*)"Targets"))
		{
			parseTargetsElement(doc,node);
		}
		node = node->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
