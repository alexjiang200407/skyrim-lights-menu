namespace SLM
{
	inline RE::NiPoint3 GetCameraPosition()
	{
		RE::NiPoint3 origin;
		if (RE::PlayerCamera::GetSingleton()->IsInFreeCameraMode())
			reinterpret_cast<RE::FreeCameraState*>(RE::PlayerCamera::GetSingleton()->currentState.get())->GetTranslation(origin);
		else
			origin = RE::PlayerCamera::GetSingleton()->pos;

		return origin;
	}


	inline RE::NiMatrix3 QuaternionToMatrix(const RE::NiQuaternion& a_quat)
	{
		float sqw = a_quat.w * a_quat.w;
		float sqx = a_quat.x * a_quat.x;
		float sqy = a_quat.y * a_quat.y;
		float sqz = a_quat.z * a_quat.z;

		RE::NiMatrix3 ret;

		// invs (inverse square length) is only required if quaternion is not already normalised
		float invs      = 1.f / (sqx + sqy + sqz + sqw);
		ret.entry[0][0] = (sqx - sqy - sqz + sqw) * invs;  // since sqw + sqx + sqy + sqz =1/invs*invs
		ret.entry[1][1] = (-sqx + sqy - sqz + sqw) * invs;
		ret.entry[2][2] = (-sqx - sqy + sqz + sqw) * invs;

		float tmp1      = a_quat.x * a_quat.y;
		float tmp2      = a_quat.z * a_quat.w;
		ret.entry[1][0] = 2.f * (tmp1 + tmp2) * invs;
		ret.entry[0][1] = 2.f * (tmp1 - tmp2) * invs;

		tmp1            = a_quat.x * a_quat.z;
		tmp2            = a_quat.y * a_quat.w;
		ret.entry[2][0] = 2.f * (tmp1 - tmp2) * invs;
		ret.entry[0][2] = 2.f * (tmp1 + tmp2) * invs;
		tmp1            = a_quat.y * a_quat.z;
		tmp2            = a_quat.x * a_quat.w;
		ret.entry[2][1] = 2.f * (tmp1 + tmp2) * invs;
		ret.entry[1][2] = 2.f * (tmp1 - tmp2) * invs;

		return ret;
	}


	inline void EulerToMatrix(RE::NiMatrix3* dst, float x, float y, float z)
	{
		dst->entry[0][0] = cos(y) * cos(z);
		dst->entry[0][1] = -cos(y) * sin(z);
		dst->entry[0][2] = sin(y);
		dst->entry[1][0] = cos(z) * sin(x) * sin(y) + cos(x) * sin(z);
		dst->entry[1][1] = cos(x) * cos(z) - sin(x) * sin(y) * sin(z);
		dst->entry[1][2] = -cos(y) * sin(x);
		dst->entry[2][0] = -cos(x) * cos(z) * sin(y) + sin(x) * sin(z);
		dst->entry[2][1] = cos(z) * sin(x) + cos(x) * sin(y) * sin(z);
		dst->entry[2][2] = cos(x) * cos(y);
	}
}