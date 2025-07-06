// xmlManager.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <stdio.h>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"

int main(int argc, char* argv[])
{

   rapidxml::file<> xmlFile("sprite.xml");
   rapidxml::xml_document<> xmlDoc;
   xmlDoc.parse<0>(xmlFile.data());

   rapidxml::xml_node<> *pRoot = xmlDoc.first_node();

   for(rapidxml::xml_node<> *pNode=pRoot->first_node("SubTexture"); pNode; pNode=pNode->next_sibling())
   {
      printf("SubTexture name %s, x: %s y: %s\n", pNode->first_attribute("name")->value(), pNode->first_attribute("x")->value(),pNode->first_attribute("y")->value());     
   }

//   int nValue = atoi(pAttr->value());
   
   xmlDoc.clear();

   return 0;
}

