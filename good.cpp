#include "good.h"

Good Good::Deserialize(JsonVariant& json)
{
    String name = json[json_name].as<String>();
    String image_path = json[json_image].as<String>();
    uint32_t price = json[json_price].as<uint32_t>();

    return Good(name, image_path, price);
}