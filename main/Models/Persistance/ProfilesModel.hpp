#pragma once

#include "RemoteModel.hpp"
#include "Preferences.hpp"
#include "Profile.hpp"

#include <array>

template <uint8_t profileCount>
class ProfilesModel
{
public:
    explicit ProfilesModel(RemoteModel *remoteModel, Preferences *preferences) : remoteModel(remoteModel), preferences(preferences) {}

private:
    std::array<Profile, profileCount> profiles;

    RemoteModel *remoteModel;
    Preferences *preferences;
};