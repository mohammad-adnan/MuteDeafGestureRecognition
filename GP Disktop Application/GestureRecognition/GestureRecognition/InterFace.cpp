#include "InterFace.h"
using namespace System;

namespace GestureRecognition{    // Change this!!
	using namespace System;
	using namespace System::Windows::Forms;

	[STAThread]
	int main(array<System::String ^> ^args)
	{
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		Application::Run(gcnew InterFace());
	
		return 0;
	}
}