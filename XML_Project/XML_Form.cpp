#include "XML_Form.h"



using namespace System;
using namespace System::Windows::Forms;



[STAThreadAttribute]
void main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    XMLProject::XML_Form form;
    Application::Run(% form);
}


