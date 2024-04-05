#include "prop.hpp"

void SLM::Prop::Remove()
{
	ref->Disable();
	ref->SetDelete(true);
}
