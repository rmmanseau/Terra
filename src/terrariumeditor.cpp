#include "terrariumeditor.h"

#define ROOT_DIR "../"
#define SPRITE_SHEET_12_PATH "assets/textures/sprite_sheet_12.png"
#define DIRT_TEXTURE_PATH "assets/textures/dirt.png"
#define DEFAULT_TERRARIUM_BLUEPRINT_PATH "assets/yaml/terrariums/default.yaml"
#define ENTITY_BLUEPRINTS_PATH "assets/yaml/entities.yaml"

void loadTerrariumBlueprint(TerrariumBlueprint& blueprint,
                            const std::string& blueprintPath)
{
    try
    {
        YAML::Node blueprintNode = YAML::LoadFile((std::string)ROOT_DIR + blueprintPath);

        blueprint.width = blueprintNode["width"].as<int>();
        blueprint.height = blueprintNode["height"].as<int>();
        blueprint.tileSize = blueprintNode["tile_size"].as<int>();
        blueprint.spriteSheetPath = blueprintNode["sprite_sheet"].as<std::string>();
        blueprint.dirtTexturePath = blueprintNode["dirt_texture"].as<std::string>();
        blueprint.dirtColor = sf::Color(blueprintNode["dirt_color"][0].as<int>(),
                                     blueprintNode["dirt_color"][1].as<int>(),
                                     blueprintNode["dirt_color"][2].as<int>());

        YAML::const_iterator itr = blueprintNode["initial_entities"].begin();
        YAML::const_iterator end = blueprintNode["initial_entities"].end();
        for (itr; itr != end; ++itr)
        {
            Vec2i position((*itr)["pos"][0].as<int>(), (*itr)["pos"][1].as<int>());
            EntityType type = G_EntityNameTypeMap[(*itr)["type"].as<std::string>()];

            blueprint.entities.insert(std::make_pair(position, type));
        }
    }
    catch (const YAML::Exception &e)
    {
        std::cout << "Error with file: " << blueprintPath << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "Starting editor with basic values." << std::endl;

        TerrariumBlueprint defaultBlueprint;
        defaultBlueprint.width = 20;
        defaultBlueprint.height = 20;
        defaultBlueprint.tileSize = 12;
        defaultBlueprint.spriteSheetPath = SPRITE_SHEET_12_PATH;
        defaultBlueprint.dirtTexturePath = DIRT_TEXTURE_PATH;
        defaultBlueprint.dirtColor = sf::Color(143, 97, 45);

        blueprint = defaultBlueprint;
    }
}

void loadRenderComponents(std::unordered_map<int, CRender>& renderComponents,
                          const std::string& renderComponentsPath)
{
    try
    {
        YAML::Node entitiesNode = YAML::LoadFile((std::string)ROOT_DIR +
                                                 renderComponentsPath);

        for (YAML::const_iterator itr = entitiesNode.begin();
             itr != entitiesNode.end(); ++itr)
        {
            EntityType type = G_EntityNameTypeMap[itr->first.as<std::string>()];
            CRender render;
            render.init((itr->second)["CRender"]);
            renderComponents.insert(std::make_pair((int)type, render));

            std::cout << (int)type << std::endl;
        }
    }
    catch (const YAML::Exception &e)
    {
        std::cout << "Error with file: " << renderComponentsPath << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "Exiting editor" << std::endl;

        throw std::invalid_argument("Terrarium blueprint editor failed to load entity blueprints");
    }
}

void addCursorToSpriteMap(SpriteMap& spriteMap, CursorInfo& cursor,
                          std::unordered_map<int, CRender>& renderComponents)
{
    Vec2i pos = cursor.position;
    CRender& render = renderComponents.at((int)cursor.type);

    for (int i = 0; i < render.layers.size(); ++i)
    {
        CRender::Layer& layer = render.layers[i];
        spriteMap.addSprite(pos, layer.texCoords, layer.color);
    }
}

void addEntitiesToSpriteMap(SpriteMap& spriteMap, TerrariumBlueprint& blueprint,
                            CursorInfo& cursor, std::unordered_map<int, CRender>& renderComponents)
{
    for (auto itr = blueprint.entities.begin();
         itr != blueprint.entities.end(); ++itr)
    {
        Vec2i pos = (itr->first);

        if (pos == cursor.position)
            continue;

        CRender& render = renderComponents.at((int)(itr->second));

        for (int i = 0; i < render.layers.size(); ++i)
        {
            CRender::Layer& layer = render.layers[i];
            spriteMap.addSprite(pos, layer.texCoords, layer.color);
        }
    }
}

void runTerrariumBlueprintEditor(std::string blueprintPath)
{
    if (blueprintPath == "NOPATH")
        blueprintPath = DEFAULT_TERRARIUM_BLUEPRINT_PATH;

    TerrariumBlueprint blueprint;
    loadTerrariumBlueprint(blueprint, blueprintPath);

    std::unordered_map<int, CRender> renderComponents;
    loadRenderComponents(renderComponents, ENTITY_BLUEPRINTS_PATH);


    int winW = blueprint.width * blueprint.tileSize;
    int winH = blueprint.height * blueprint.tileSize;
    sf::RenderWindow window(sf::VideoMode(winW, winH, 32),
                            "Terra - Editor",
                            sf::Style::Close);
    window.setMouseCursorVisible(false);

    CursorInfo cursor;
    cursor.type = (EntityType)3;
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    cursor.position = Vec2i(pos.x / blueprint.tileSize,
                            pos.y / blueprint.tileSize);
    sf::Event event;

    Background background(winW, winH, blueprint.dirtTexturePath, blueprint.dirtColor);
    SpriteMap spriteMap(blueprint.tileSize, blueprint.spriteSheetPath);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }

                case sf::Event::MouseMoved:
                {
                    cursor.position = Vec2i(event.mouseMove.x / blueprint.tileSize,
                                            event.mouseMove.y / blueprint.tileSize);
                    break;
                }

                case sf::Event::MouseWheelMoved:
                {
                    int typeInt = (int)cursor.type;
                    typeInt = clamp(typeInt + event.mouseWheel.delta,
                                    3, (int)G_EntityNameTypeMap.size() - 1);
                    std::cout << "type: " << typeInt << std::endl;
                    cursor.type = (EntityType)typeInt;
                }
            }
        }

        spriteMap.clearSprites();
        addCursorToSpriteMap(spriteMap, cursor, renderComponents);
        addEntitiesToSpriteMap(spriteMap, blueprint, cursor, renderComponents);

        window.draw(background);
        window.draw(spriteMap);
        window.display();
    }
}