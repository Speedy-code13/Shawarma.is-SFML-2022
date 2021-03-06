#pragma once


enum button_states { BTN_IDLE, BTN_HOVER, BTN_ACTIVE };

namespace gui
{
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;
		//Variables
		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;


		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;


	public:
		//Constructor / Deconstructor
		Button(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned characterSize,
			sf::Color text_idle_color, 
			sf::Color text_hover_color, sf::Color text_active_color,	
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();

		//Acessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned getId() const;
		const sf::Vector2f getSize() const;
		const sf::FloatRect getGlobalBounds() const;


		void setText(const std::string& text);
		void setId(const unsigned short Id);	
		void setPosition(float x, float y);

		//Functions
		void update(const sf::Vector2f& mousePos);
		void render(std::shared_ptr<sf::RenderWindow> target);
		void render(sf::RenderTarget& target);

	};

	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;
		unsigned numberOfElements;
		float height;

	public:
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned numberOfElements,  unsigned default_index = 0);
		virtual ~DropDownList();
			
		const unsigned short getActiveElementId() const;
		void setActiveElementId(const unsigned short id);
		//Functons
		const bool getKetime();
		const sf::Vector2f getSize() const;
		void setPosition(float x, float y);
		void updateKeytime(const float& dt);
		void update(sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class TextureSelector
	{
	private:
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;
		float gridSize;
		bool active;
		
	public:
		TextureSelector(float x, float y, float width, float height, float grid_size, const sf::Texture* texture_sheet);
		~TextureSelector();

		//Accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;
		void setPosition(float x, float y);

		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget& target);
	};

}


