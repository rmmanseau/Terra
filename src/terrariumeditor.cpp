#include "terrariumeditor.h"

#define ROOT_DIR "../"
#define SPRITE_SHEET_12_PATH "assets/textures/sprite_sheet_12.png"
#define DIRT_TEXTURE_PATH "assets/textures/dirt.png"
#define DEFAULT_TERRARIUM_BLUEPRINT_PATH "assets/yaml/terrariums/default.yaml"
#define ENTITY_BLUEPRINTS_PATH "assets/yaml/entities.yaml"

void TerrariumEditor::loadBlueprint(const std::string& blueprintPath)
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

        Blueprint defaultBlueprint;
        defaultBlueprint.width = 20;
        defaultBlueprint.height = 20;
        defaultBlueprint.tileSize = 12;
        defaultBlueprint.spriteSheetPath = SPRITE_SHEET_12_PATH;
        defaultBlueprint.dirtTexturePath = DIRT_TEXTURE_PATH;
        defaultBlueprint.dirtColor = sf::Color(143, 97, 45);

        blueprint = defaultBlueprint;
    }
}

void TerrariumEditor::saveBlueprint(const std::string& blueprintName)
{
    std::ofstream savefile;
    savefile.open("../assets/yaml/terrariums/" + blueprintName + ".yaml");

    std::map<int, std::string> EntityTypeToNameMap;
    for (auto itr = G_EntityNameTypeMap.begin();
         itr != G_EntityNameTypeMap.end(); ++itr)
    {
        EntityTypeToNameMap.insert(std::make_pair(itr->second, itr->first));
    }

    YAML::Emitter out;
    out.SetIndent(4);
    out << YAML::BeginMap
        << YAML::Key << "width" << YAML::Value << blueprint.width
        << YAML::Key << "height" << YAML::Value << blueprint.height 
        << YAML::Key << "tile_size" << YAML::Value << blueprint.tileSize 
        << YAML::Key << "sprite_sheet" << YAML::Value << blueprint.spriteSheetPath 
        << YAML::Key << "dirt_texture" << YAML::Value << blueprint.dirtTexturePath
        << YAML::Key << "dirt_color" << YAML::Value
            << YAML::Flow << YAML::BeginSeq
            << (int)blueprint.dirtColor.r
            << (int)blueprint.dirtColor.g
            << (int)blueprint.dirtColor.b
            << YAML::EndSeq
        << YAML::Key << "initial_entities" << YAML::Value
            << YAML::BeginSeq;

    for (auto itr = blueprint.entities.begin();
         itr != blueprint.entities.end(); ++itr)
    {
        Vec2i pos = (itr->first);
        if (pos.x >= 0 && pos.x < blueprint.width &&
            pos.y >= 0 && pos.y < blueprint.height)
        {
            out << YAML::Flow << YAML::BeginMap
                << YAML::Key << "type"
                << YAML::Value << EntityTypeToNameMap.at(itr->second)
                << YAML::Key << "pos"
                << YAML::Value
                    << YAML::Flow << YAML::BeginSeq
                    << pos.x
                    << pos.y
                    << YAML::EndSeq
                << YAML::EndMap;
        }
    }

    out << YAML::EndSeq << YAML::EndMap;

    savefile << out.c_str() << std::endl;
    savefile.close();
}

void TerrariumEditor::loadRenderComponents(const std::string& renderComponentsPath)
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

void TerrariumEditor::addCursorToSpriteMap()
{
    Vec2i pos = cursor.position;
    CRender& render = renderComponents.at((int)cursor.type);

    for (int i = 0; i < render.layers.size(); ++i)
    {
        CRender::Layer& layer = render.layers[i];
        spriteMap.addSprite(pos, layer.texCoords, layer.color);
    }

    spriteMap.addSprite(pos, Vec2i(11, 11), sf::Color::White);
}

void TerrariumEditor::addEntitiesToSpriteMap()
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

void resizeEditor(Vec2i delta, TerrariumEditor& editor, sf::RenderWindow& window)
{
    editor.blueprint.width += delta.x;
    editor.blueprint.height += delta.y;

    int winW = editor.blueprint.width * editor.blueprint.tileSize;
    int winH = editor.blueprint.height * editor.blueprint.tileSize;

    editor.background.setSize(winW, winH);

    sf::FloatRect visibleArea(0, 0, winW, winH);
    window.setView(sf::View(visibleArea));
    window.setSize(sf::Vector2u(winW, winH));
}

TerrariumEditor::TerrariumEditor(const std::string& blueprintPath, const std::string& entityBlueprintsPath)
{
    loadBlueprint(blueprintPath);
    loadRenderComponents(entityBlueprintsPath);
    int winW = blueprint.width * blueprint.tileSize;
    int winH = blueprint.height * blueprint.tileSize;
    background.init(winW, winH, blueprint.dirtTexturePath, blueprint.dirtColor);
    spriteMap.init(blueprint.tileSize, blueprint.spriteSheetPath);

    cursor.type = (EntityType)3;
    cursor.resizingWindow = false;
}

void TerrariumEditor::updateSpriteMap()
{
    spriteMap.clearSprites();
    addEntitiesToSpriteMap();
    addCursorToSpriteMap();
}

void TerrariumEditor::drawBlueprint(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(spriteMap);
}

void runTerrariumBlueprintEditor(std::string blueprintPath)
{
    if (blueprintPath == "NOPATH")
        blueprintPath = DEFAULT_TERRARIUM_BLUEPRINT_PATH;

    TerrariumEditor editor(blueprintPath, ENTITY_BLUEPRINTS_PATH);

    WindowState windowState = WindowState::idle; 

    int winW = editor.blueprint.width * editor.blueprint.tileSize;
    int winH = editor.blueprint.height * editor.blueprint.tileSize;
    sf::RenderWindow window(sf::VideoMode(winW, winH, 32),
                            "Terra - Editor",
                            sf::Style::Close);
    window.setMouseCursorVisible(false);

    sf::Vector2i pos = sf::Mouse::getPosition(window);
    editor.cursor.position = Vec2i(pos.x / editor.blueprint.tileSize,
                                   pos.y / editor.blueprint.tileSize);

    sf::Event event;
    
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(event.type == sf::Event::MouseMoved)
            {
                Vec2i newPosition(event.mouseMove.x / editor.blueprint.tileSize,
                                  event.mouseMove.y / editor.blueprint.tileSize);

                if (editor.cursor.resizingWindow)
                {
                    Vec2i delta = newPosition - editor.cursor.position;
                    resizeEditor(delta, editor, window);
                    winW = editor.blueprint.width * editor.blueprint.tileSize;
                    winH = editor.blueprint.height * editor.blueprint.tileSize;
                }

                if (!editor.cursor.resizingWindow &&
                    sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    editor.blueprint.entities[editor.cursor.position] = editor.cursor.type;
                }

                if (!editor.cursor.resizingWindow &&
                    sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    editor.blueprint.entities.erase(editor.cursor.position);
                }

                editor.cursor.position = newPosition;
            }

            if(event.type == sf::Event::MouseWheelMoved)
            {
                int typeInt = (int)editor.cursor.type;
                typeInt = clamp(typeInt + event.mouseWheel.delta,
                                3, (int)G_EntityNameTypeMap.size() - 1);
                editor.cursor.type = (EntityType)typeInt;
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left &&
                    sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
                    editor.cursor.resizingWindow == false)
                {
                    editor.cursor.resizingWindow = true;
                }

                if (!editor.cursor.resizingWindow &&
                    sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    editor.blueprint.entities[editor.cursor.position] = editor.cursor.type;
                }

                if (!editor.cursor.resizingWindow &&
                    sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    editor.blueprint.entities.erase(editor.cursor.position);
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                editor.cursor.resizingWindow = false;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::S)
                {
                    std::string blueprintName;
                    getInput(blueprintName);

                    editor.saveBlueprint(blueprintName);
                }
            }
        
            editor.updateSpriteMap();
            editor.drawBlueprint(window);

            window.display();
        }
        sf::sleep(sf::microseconds(100));
    }
}