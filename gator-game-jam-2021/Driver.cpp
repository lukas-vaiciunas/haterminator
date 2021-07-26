#include "Driver.h"
#include "Menu.h"
#include "CharacterSelect.h"
#include "Game.h"
#include "Event.h"

Driver::Driver() :
	Listener({ EventType::ChangeDriverState, EventType::ChangePlayerAnimations }),
	eventQueue_(EventQueue::instance()),
	menu_(nullptr),
	game_(nullptr),
	animations_(),
	mouse_(),
	keyboard_(),
	state_(DriverState::None),
	isDone_(false)
{
	this->changeState_(DriverState::Menu);
}

Driver::~Driver()
{
	this->changeState_(DriverState::None);
}

void Driver::onEvent(const Event &ev)
{
	if (ev.eventType() == EventType::ChangeDriverState)
	{
		EventChangeDriverState trueEvent = static_cast<const EventChangeDriverState &>(ev);

		this->changeState_(trueEvent.driverState());
	}
	else if (ev.eventType() == EventType::ChangePlayerAnimations)
	{
		EventChangePlayerAnimations trueEvent = static_cast<const EventChangePlayerAnimations &>(ev);

		animations_ = trueEvent.animations();
	}
}

void Driver::updateOnTick()
{
	eventQueue_.dispatch();

	switch (state_)
	{
	case DriverState::Menu:
		menu_->updateOnTick();
		break;
	case DriverState::CharacterSelect:
		characterSelect_->updateOnTick();
		break;
	case DriverState::Play:
		game_->updateOnTick(keyboard_, mouse_);
		break;
	}
}

void Driver::updateOnMouseAxes(ALLEGRO_EVENT &ev)
{
	mouse_.updateOnAxes(ev);

	switch (state_)
	{
	case DriverState::Menu:
		menu_->updateOnMouseAxes(mouse_);
		break;
	case DriverState::CharacterSelect:
		characterSelect_->updateOnMouseAxes(mouse_);
		break;
	case DriverState::Play:
		game_->updateOnMouseAxes(mouse_);
		break;
	}
}

void Driver::updateOnMousePress(ALLEGRO_EVENT &ev)
{
	mouse_.updateOnPress(ev);

	switch (state_)
	{
	case DriverState::Menu:
		menu_->updateOnMousePress(mouse_);
		break;
	case DriverState::CharacterSelect:
		characterSelect_->updateOnMousePress(mouse_);
		break;
	case DriverState::Play:
		game_->updateOnMousePress(mouse_);
		break;
	}
}

void Driver::updateOnMouseRelease(ALLEGRO_EVENT &ev)
{
	mouse_.updateOnRelease(ev);
}

void Driver::updateOnKeyPress(ALLEGRO_EVENT &ev)
{
	keyboard_.updateOnPress(ev);

	switch (state_)
	{
	case DriverState::Play:
		game_->updateOnKeyPress(keyboard_);
		break;
	}
}

void Driver::updateOnKeyRelease(ALLEGRO_EVENT &ev)
{
	keyboard_.updateOnRelease(ev);
}

void Driver::updateOnDisplayClose()
{
	isDone_ = true;
}

void Driver::render() const
{
	switch (state_)
	{
	case DriverState::Menu:
		menu_->render();
		break;
	case DriverState::CharacterSelect:
		characterSelect_->render();
		break;
	case DriverState::Play:
		game_->render();
		break;
	}
}

void Driver::changeState_(DriverState toState)
{
	switch (state_)
	{
	case DriverState::Menu:
		delete menu_;
		menu_ = nullptr;
		break;
	case DriverState::CharacterSelect:
		delete characterSelect_;
		characterSelect_ = nullptr;
		break;
	case DriverState::Play:
		delete game_;
		game_ = nullptr;
		break;
	}

	state_ = toState;

	switch (state_)
	{
	case DriverState::Menu:
		menu_ = new Menu();
		break;
	case DriverState::CharacterSelect:
		characterSelect_ = new CharacterSelect();
		break;
	case DriverState::Play:
		game_ = new Game(animations_);
		break;
	case DriverState::Quit:
		isDone_ = true;
		break;
	}
}

bool Driver::isDone() const
{
	return isDone_;
}