#include "prop.hpp"

void SLM::Prop::RemoveProp()
{
	ref->Disable();
	ref->SetDelete(true);
}
