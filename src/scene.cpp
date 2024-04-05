#include "scene.hpp"
#include "logger.hpp"

void SLM::Scene::PlaceProp(RE::TESBoundObject* obj)
{
	RE::TESObjectREFR* playerRef = RE::PlayerCharacter::GetSingleton()->AsReference();

	if (!playerRef)
	{
		logger::warn("Could not find player reference");
		return;
	}

	RE::NiPoint3 collision = RE::CrosshairPickData::GetSingleton()->collisionPoint;
	RE::NiPoint3 origin;
	RE::NiPoint3 directionVec;

	RE::PlayerCharacter::GetSingleton()->GetEyeVector(origin, directionVec, false);

	directionVec *= 50.0f;

	// X metres ahead of player
	RE::NiPoint3 lookingAt = origin + directionVec;

	auto newPropRef = RE::TESDataHandler::GetSingleton()->CreateReferenceAtLocation(
		obj, lookingAt, { 0.0f, 0.0f, 0.0f }, playerRef->GetParentCell(), nullptr,
		nullptr, nullptr, {}, true, false).get();

	props.push_back(newPropRef);
}

void SLM::Scene::ClearScene()
{
	for (auto& prop : props)
		prop.Remove();

	props.clear();
}
