#include "terrariumeditor.h"

#define ROOT_DIR "../"
#define SPRITE_SHEET_12_PATH "assets/textures/sprite_sheet_12.png"
#define DIRT_TEXTURE_PATH "assets/textures/dirt.png"
#define DEFAULT_TERRARIUM_BLUEPRINT_PATH "assets/yaml/terrariums/default.yaml"
#define ENTITY_BLUEPRINTS_PATH "assets/yaml/entities.yaml"

TerrariumEditor::TerrariumEditor(const std::string& blueprintPath, const std::string& entityBlueprintsPath)
{
    loadBlueprint(blueprintPath);
    loadRenderComponents(entityBlueprintsPath);
    int winW = blueprint.width * blueprint.tileSize;
    int winH = blueprint.height * blueprint.tileSize;
    background.init(winW, winH, blueprint.dirtTexturePath, blueprint.dirtColor);
    spriteMap.init(blueprint.tileSize, blueprint.spriteSheetPath);
    state = State::idle;

    cursor.type = (EntityType)3;
    cursor.resizingWindow = false;
}

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

void TerrariumEditor::resize(Vec2i delta, sf::RenderWindow& window)
{
    blueprint.width += delta.x;
    blueprint.height += delta.y;

    int winW = blueprint.width * blueprint.tileSize;
    int winH = blueprint.height * blueprint.tileSize;

    background.setSize(winW, winH);

    sf::FloatRect visibleArea(0, 0, winW, winH);
    window.setView(sf::View(visibleArea));
    window.setSize(sf::Vector2u(winW, winH));
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

void TerrariumEditor::changeCursorType(int change)
{
    int type = clamp((int)cursor.type + change,
                     3,
                     (int)G_EntityNameTypeMap.size() - 1);
    
    cursor.type = (EntityType)type;
}

void TerrariumEditor::setState(State newState)
{
    state = newState;
}

void TerrariumEditor::placeEntityAtCursor()
{
    blueprint.entities[cursor.position] = cursor.type;
}

void TerrariumEditor::removeEntityAtCursor()
{
    blueprint.entities.erase(cursor.position);
}

void TerrariumEditor::update(sf::RenderWindow& window, sf::Event& event)
{
    if (event.type == sf::Event::Closed)
    {
        window.close();
    }

    sf::Vector2i rawPos = sf::Mouse::getPosition(window);
    cursor.previousPosition = cursor.position;
    cursor.position = Vec2i(rawPos.x, rawPos.y) / blueprint.tileSize;

    switch (state)
    {
        case State::idle:
        {
            if (event.type == sf::Event::MouseWheelMoved)
            {
                changeCursorType(event.mouseWheel.delta);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                    sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                {
                    setState(State::resizing);
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    placeEntityAtCursor();
                    setState(State::drawing);
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    removeEntityAtCursor();
                    setState(State::erasing);
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::S)
                {
                    std::string blueprintName;
                    getInput(blueprintName);

                    saveBlueprint(blueprintName);
                }
            }

        } break;

        case State::resizing:
        {
            if (event.type == sf::Event::MouseButtonReleased)
            {
                setState(State::idle);
            }

            if (event.type == sf::Event::MouseMoved)
            {
                Vec2i delta = cursor.position - cursor.previousPosition;
                resize(delta, window);
            }

        } break;

        case State::drawing:
        {
            if (event.type == sf::Event::MouseButtonReleased)
            {
                setState(State::idle);
            }

            if (event.type == sf::Event::MouseMoved)
            {
                placeEntityAtCursor();
            }

        } break;

        case State::erasing:
        {
            if (event.type == sf::Event::MouseButtonReleased)
            {
                setState(State::idle);
            }

            if (event.type == sf::Event::MouseMoved)
            {
                removeEntityAtCursor();
            }

        } break;
    }
    
    updateSpriteMap();
    drawBlueprint(window);

    window.display();  

    std::cout << (int)state << std::endl;
}

void runTerrariumBlueprintEditor(std::string blueprintPath)
{
    if (blueprintPath == "NOPATH")
        blueprintPath = DEFAULT_TERRARIUM_BLUEPRINT_PATH;

    TerrariumEditor editor(blueprintPath, ENTITY_BLUEPRINTS_PATH);

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
            editor.update(window, event);
        }
        
        sf::sleep(sf::microseconds(100));
    }
}