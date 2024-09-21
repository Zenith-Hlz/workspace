#include "tinyxml2.h"
#include <iostream>

using namespace tinyxml2;

void create()
{
    XMLDocument doc;
    XMLDeclaration *declaration = doc.NewDeclaration();
    doc.InsertEndChild(declaration);
    XMLElement *root = doc.NewElement("Root");
    doc.InsertEndChild(root);
    XMLElement *child = doc.NewElement("Child");
    child->SetText("Hello, World!");
    root->InsertEndChild(child);
    XMLText *textNode = doc.NewText("TextContent");
    child->InsertEndChild(textNode);
    XMLElement *AAA = doc.NewElement("AAA");
    root->InsertFirstChild(AAA);
    XMLElement *BBB = doc.NewElement("BBB");
    root->InsertAfterChild(AAA, BBB);
    XMLElement *CCC = doc.NewElement("CCC");
    CCC->SetText("This is text of CCC.");
    AAA->InsertEndChild(CCC);
    XMLComment *comment = doc.NewComment("This is a comment");
    doc.InsertEndChild(comment);
    doc.SaveFile("example.xml");
}

void modify()
{
    XMLDocument doc;
    if (doc.LoadFile("example.xml") == XML_SUCCESS)
    {
        XMLElement *root = doc.RootElement();
        XMLElement *nodeToModify1 = root->FirstChildElement("AAA");
        XMLElement *nodeToModify2 = root->FirstChildElement("BBB");
        XMLElement *nodeToModify3 = nodeToModify1->FirstChildElement("CCC");
        nodeToModify1->SetName("NewName");
        nodeToModify1->SetText("NewText");
        nodeToModify1->SetAttribute("sing", "dance");
        nodeToModify1->SetAttribute("cxk", "ikun");
        nodeToModify2->SetAttribute("rap", "basketball");
        nodeToModify2->SetAttribute("giegie", 2.5);
        nodeToModify1->DeleteChild(nodeToModify3);
        doc.SaveFile("example_modified.xml");
    }
}

void read()
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile("example_modified.xml");
    tinyxml2::XMLElement *root = doc.RootElement();
    tinyxml2::XMLElement *firstNode = root->FirstChildElement();
    if (firstNode)
    {
        std::string nodeName = firstNode->Name();
        printf("node name is %s\n", nodeName.c_str());
        std::string nodeConrtext = firstNode->GetText();
        printf("node text is %s\n", nodeConrtext.c_str());
        const char *attrNameValue = firstNode->Attribute("sing");
        std::cout << "Parameter name value: " << attrNameValue << std::endl;
        const tinyxml2::XMLAttribute *attr = firstNode->FirstAttribute();
        while (attr)
        {
            std::string attrName = attr->Name();
            std::string attrValue = attr->Value();
            printf("param name is: %s, param value is: %s\n", attrName.c_str(), attrValue.c_str());
            attr = attr->Next();
        }
    }
}

int main()
{
#ifdef _test_1_
    create();
#endif
#ifdef _test_2_
    modify();
#endif
#ifdef _test_3_
    read();
#endif
    return 0;
}
