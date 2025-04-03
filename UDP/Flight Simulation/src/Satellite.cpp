#include "Satellite.h"

#include <cstdlib>

Satellite::Satellite()
{
    data = Data{0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f};
}

void Satellite::UpdateData()
{
    data = {(std::rand() % 2) * 0.1f, (std::rand() % 4) * 0.1f, (std::rand() % 2) * 0.1f,
            data.pitch + 5.0f, data.yaw + 5.0f, data.roll + 5.0f};
}

Data Satellite::GetData() const { return data; }