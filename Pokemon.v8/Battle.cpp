#include "Battle.h"

Battle::Battle(Trainer* p, Trainer* o) : player_(p), opponent_(o) {}

void Battle::Intro()
{
	std::cout << opponent_->name_ << " wants to battle!" << std::endl << std::endl;
	std::cout << opponent_->name_ << " sent out " << opponent_pokemon_->name_ << "!" << std::endl << std::endl;
	std::cout << "Go! " << player_pokemon_->name_ << "!" << std::endl << std::endl;
	player_pokemon_->active_ = true;
}

//frill for showing stats
void Battle::ShowStatus()
{
	std::cout << "            " << opponent_pokemon_->name_ << std::endl;
	std::cout << "            " << "HP: " << int(opponent_pokemon_->currenthealth_) << "/" << opponent_pokemon_->maxhealth_ << std::endl;
	std::cout << std::endl << std::endl << std::endl;
	std::cout << player_pokemon_->name_ << std::endl;
	std::cout << "HP: " << int(player_pokemon_->currenthealth_) << "/" << player_pokemon_->maxhealth_ << std::endl;
}

int Battle::MainMenu()
{
	
	int answer = 0;
	std::cout << "************************" << std::endl;
	std::cout << "1. Attack" << "       " << "2. Bag" << std::endl << "3. Pokemon" << "      " << "4. Run" << std::endl;
	std::cout << "************************" << std::endl;
	std::cout << std::endl;
	while (answer < 1 || answer > 4)
	{
		std::cout << "Choice: ";
		std::cin >> answer;
		if (std::find(player_pokemon_->status_.begin(), player_pokemon_->status_.end(), Status::Charging) != player_pokemon_->status_.end() || !player_pokemon_->visible_) {
			player_pokemon_->attackcounter++;
			return 0;
		}
	}
	return answer;
}

bool Battle::UserNoMorePokemon()
{
	std::vector<Pokemon> AlivePokemon;
	for (Pokemon p : *player_pokemons_)
	{
		if (std::find(p.status_.begin(), p.status_.end(), Status::Fainted) == p.status_.end())
		{
			AlivePokemon.push_back(p);
		}
	}
	if (AlivePokemon.size() > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool Battle::OpponentNoMorePokemon()
{
	std::vector<Pokemon> AlivePokemon;
	for (Pokemon p : *opponent_pokemons_)
	{
		if (std::find(p.status_.begin(), p.status_.end(), Status::Fainted) == p.status_.end())
		{
			AlivePokemon.push_back(p);
		}
	}
	if (AlivePokemon.size() > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Battle::MainBattleLoop()
{
	Intro();
	while (!UserNoMorePokemon() && !OpponentNoMorePokemon())
	{
		BattleLoop();
		if (std::find(player_pokemon_->status_.begin(), player_pokemon_->status_.end(), Status::Fainted) != player_pokemon_->status_.end())
		{
			if (UserNoMorePokemon())
			{
				break;
			}
			SwitchPokemon();
			SwitchDeclaration();
		}
		else if (std::find(opponent_pokemon_->status_.begin(), opponent_pokemon_->status_.end(), Status::Fainted) != opponent_pokemon_->status_.end())
		{

			if (OpponentNoMorePokemon())
			{
				break;
			}
			OpponentSwitchPokemon();
		}
	}
	if (OpponentNoMorePokemon())
	{
		std::cout << "You defeated " << opponent_->name_ << "!" << std::endl;
	}
	else
	{
		std::cout << "You lost!" << std::endl;
	}
}

//***************************i think we're totally good up here.***************************************************

void Battle::SwitchPokemon()
{
	while (true)
	{
		std::cout << "Choose a pokemon:" << std::endl;
		size_t pokemons = 0;
		for (pokemons; pokemons < player_pokemons_->size(); pokemons++)
		{
			std::cout << (pokemons + 1) << ". " << player_pokemons_->at(pokemons).name_ << std::endl;
		}
		std::cout << pokemons + 1 << ". Back" << std::endl;
		size_t answer = 100;

		while (answer > (pokemons + 1) || answer < 1)
		{
			std::cout << "Choice: ";
			std::cin >> answer;
		}
		if (answer == pokemons + 1)
		{
			return;
		}
		std::cout << "Would you like to send out " << player_pokemons_->at(answer - 1).name_ << "?" << std::endl;
		std::cout << "1. Yes" << std::endl << "2. No" << std::endl;
		int answer2 = 0;
		while (answer2 > 2 || answer2 < 1)
		{
			std::cout << "Choice: ";
			std::cin >> answer2;
		}
		if (answer2 == 1)
		{
			if (std::find(player_pokemons_->at(answer - 1).status_.begin(), player_pokemons_->at(answer - 1).status_.end(), Status::Fainted) != player_pokemons_->at(answer - 1).status_.end())
			{
				std::cout << "That pokemon is down!" << std::endl;
			}
			else if (player_pokemon_ == &(player_pokemons_->at(answer - 1)))
			{
				std::cout << "That pokemon is already in battle!" << std::endl;
			}
			else
			{
				player_next_pokemon_ = &(player_pokemons_->at(answer - 1));
				return;
			}
		}
		else
		{
			return;
		}
	}
}

void Battle::SwitchDeclaration()
{
	std::string declare;
	std::string a = ", enough! Come back!";
	std::string b = ", good! Return!";
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(1, 2);
	int rand = distribution(generator);
	if (rand == 1)
	{
		declare = a;
	}
	else
	{
		declare = b;
	}

	std::cout << player_pokemon_->name_ << declare << std::endl;
	player_pokemon_ = player_next_pokemon_;
	player_next_pokemon_ = nullptr;
	std::cout << player_pokemon_->name_ << ", I choose you!" << std::endl;
}

void Battle::OpponentSwitchPokemon()
{
	std::vector<Pokemon*> AlivePokemon;
	for (size_t i = 0; i < opponent_pokemons_->size(); i++)
	{
		Pokemon* pokemon = &(opponent_pokemons_->at(i));
		if (std::find(pokemon->status_.begin(), pokemon->status_.end(), Status::Fainted) == pokemon->status_.end())
		{
			AlivePokemon.push_back(pokemon);
		}
	}
	Pokemon* nextpokemon = AlivePokemon.at(0);
	std::cout << opponent_->name_ << " is about to send out " << nextpokemon->name_ << std::endl;
	std::cout << "Will " << player_->name_ << " change pokemon?: " << std::endl;
	std::cout << "1: Yes" << std::endl << "2: No" << std::endl;
	int answer = 3;
	while ((answer != 1) && (answer != 2))
	{
		std::cout << "Choice: ";
		std::cin >> answer;
	}
	if (answer == 1)
	{
		SwitchPokemon();
		SwitchDeclaration();
	}
	std::cout << opponent_->name_ << " sent out " << nextpokemon->name_ << "!" << std::endl;
	opponent_pokemon_ = nextpokemon;
}

//******************************where the actual hard part starts**************************************************

void Battle::CalculatePriority(Move* playermove, Move* opponentmove)
{
	if (playermove->priority > opponentmove->priority)
	{
		UseMove(playermove, player_pokemon_, opponent_pokemon_);
		player_move_ = nullptr;
		if (opponent_pokemon_->currenthealth_ <= 0)
		{
			return;
		}
		UseMove(opponentmove, opponent_pokemon_, player_pokemon_);
		opponent_move_ = nullptr;
	}
	else if (opponentmove->priority > playermove->priority)
	{
		UseMove(opponentmove, opponent_pokemon_, player_pokemon_);
		opponent_move_ = nullptr;
		if (player_pokemon_->currenthealth_ <= 0)
		{
			return;
		}
		UseMove(playermove, player_pokemon_, opponent_pokemon_);
		player_move_ = nullptr;
	}
	else
	{
		if (player_pokemon_->speed_ > opponent_pokemon_->speed_)
		{
			UseMove(playermove, player_pokemon_, opponent_pokemon_);
			player_move_ = nullptr;
			if (opponent_pokemon_->currenthealth_ <= 0)
			{
				return;
			}
			UseMove(opponentmove, opponent_pokemon_, player_pokemon_);
			opponent_move_ = nullptr;
		}
		else
		{
			UseMove(opponentmove, opponent_pokemon_, player_pokemon_);
			opponent_move_ = nullptr;
			if (player_pokemon_->currenthealth_ <= 0)
			{
				return;
			}
			UseMove(playermove, player_pokemon_, opponent_pokemon_);
			player_move_ = nullptr;
		}
	}
}

//actual main loop per pokemon battle
void Battle::BattleLoop()
{
	while ((std::find(player_pokemon_->status_.begin(), player_pokemon_->status_.end(), Status::Fainted) == player_pokemon_->status_.end()) || std::find(opponent_pokemon_->status_.begin(), opponent_pokemon_->status_.end(), Status::Fainted) == opponent_pokemon_->status_.end())
	{
		player_pokemon_->active_ = true;
		opponent_pokemon_->active_ = true;
		ShowStatus();
		//user and opponent makes their moves 
		UserMakesChoice();
		OpponentMakesChoice();
		if (player_move_ != nullptr)
		{
			if (opponent_move_ != nullptr)
			{
				CalculatePriority(player_move_, opponent_move_);
			}
			else
			{
				if (opponent_item != nullptr)
				{
					UseItem(opponent_item, opponent_, opponent_pokemon_);
					if (player_pokemon_->currenthealth_ <= 0)
					{
						return;
					}
					UseMove(player_move_, player_pokemon_, opponent_pokemon_);
					opponent_move_ = nullptr;
				}
				else if (opponent_next_pokemon_ != nullptr)
				{
					UseMove(player_move_, player_pokemon_, opponent_pokemon_);
					if (opponent_pokemon_->currenthealth_ <= 0)
					{
						return;
					}
				}
				else
				{
					UseMove(player_move_, player_pokemon_, opponent_pokemon_);

				}
			}
		}
		else if (player_item_ != nullptr)
		{
			UseItem(player_item_, player_, player_item_pokemon);
			player_item_ = nullptr;
			player_item_pokemon = nullptr;
			if (opponent_move_ != nullptr)
			{
				UseMove(opponent_move_, opponent_pokemon_, player_pokemon_);
				opponent_move_ = nullptr;
			}
			else if (opponent_item != nullptr)
			{
				UseItem(opponent_item, opponent_, opponent_pokemon_);
				opponent_item = nullptr;
			}
		}
		else if (player_next_pokemon_ != nullptr)
		{
			SwitchDeclaration();
			if (opponent_move_ != nullptr)
			{
				UseMove(opponent_move_, opponent_pokemon_, player_pokemon_);
				opponent_move_ = nullptr;
				if (player_pokemon_->currenthealth_ <= 0)
				{
					return;
				}
			}
			else if (opponent_item != nullptr)
			{
				UseItem(opponent_item, opponent_, opponent_pokemon_);
			}
		}
		if (player_pokemon_->currenthealth_ <= 0)
		{
			player_pokemon_->status_ = { Status::Fainted };
			std::cout << player_pokemon_->name_ << " fainted!" << std::endl;
			std::cout << std::endl;
			if (opponent_pokemon_->currenthealth_ <= 0)
			{
				opponent_pokemon_->status_ = { Status::Fainted };
				std::cout << opponent_pokemon_->name_ << " fainted!" << std::endl;
				std::cout << std::endl;
			}
			break;
		}
		if (opponent_pokemon_->currenthealth_ <= 0)
		{
			opponent_pokemon_->status_ = { Status::Fainted };
			std::cout << opponent_pokemon_->name_ << " fainted!" << std::endl;
			std::cout << std::endl;
			if (player_pokemon_->currenthealth_ <= 0)
			{
				player_pokemon_->status_ = { Status::Fainted };
				std::cout << player_pokemon_->name_ << " fainted!" << std::endl;
				std::cout << std::endl;
			}
			break;
		}

	}
}


void Battle::PlayerWaits()
{
	if (player_pokemon_->attackcounter == player_future_move_->effect_amount_)
	{
		player_move_ = player_future_move_;
		player_future_move_ = nullptr;
	}
	else if ((std::find(player_pokemon_->status_.begin(), player_pokemon_->status_.end(), Status::Charging) != player_pokemon_->status_.end()) && player_pokemon_->attackcounter != 0)
	{
		UserChooseMove();
	}
	else
	{
		return;
	}
}

void Battle::UserMakesChoice()
{

	while (true)
	{
		int i = MainMenu();
		if (i == 0)
		{
			PlayerWaits();
			return;
		}
		if (i == 1)
		{
			UserChooseMove();
			if (player_move_ != nullptr)
			{
				return;
			}
			
		}
		else if (i == 2)
		{
			ChooseItem();
			if (player_item_ != nullptr)
				{
					return;
				}
		}
		else if (i == 3)
		{
			SwitchPokemon();
			if (player_next_pokemon_ != nullptr)
			{
				return;
			}
		}
		else if (i == 4)
		{
			std::cout << "Where do you think you're running to?! Come back here!" << std::endl;
		}
		else
		{
			return;
		}
	}
}

void Battle::OpponentMakesChoice()
{
	if (opponent_future_move_ != nullptr)
	{
		opponent_pokemon_->attackcounter++;
		if (opponent_pokemon_->attackcounter == opponent_future_move_->effect_amount_)
		{
			opponent_move_ = opponent_future_move_;
			opponent_future_move_ = nullptr;
			return;
		}
		else if ((std::find(opponent_pokemon_->status_.begin(), opponent_pokemon_->status_.end(), Status::Charging) != opponent_pokemon_->status_.end()) && opponent_pokemon_->attackcounter != 0)
		{
			OpponentChooseMove();
			return;
		}
		else
		{
			return;
		}
	}
	else
	{
		/*std::random_device device;
		std::mt19937 generator(device());
		std::uniform_int_distribution<int> distribution(1, 100);
		int rand = distribution(generator);
		if (opponent_pokemon_->currenthealth_ > (opponent_pokemon_->maxhealth_) * .5f)
		{
			OpponentChooseMove();
		}
		else if (opponent_pokemon_->currenthealth_ < (opponent_pokemon_->maxhealth_) * .25f)
		{
			if (rand > 70)
			{
				OpponentChooseItem();
			}
			else
			{
				OpponentChooseMove();
			}
		}*/
		OpponentChooseMove();
	}
}

void Battle::UserChooseMove()
{
	std::cout << std::endl;
	std::cout << "What should " << player_pokemon_->name_ << " do?" << std::endl;
	std::cout << std::endl;
	size_t i = 0;
	for (i; i < player_pokemon_->AttackList.size(); i++)
	{
		std::cout << (i + 1) << ". " << player_pokemon_->AttackList[i].name_ << " PP: " << player_pokemon_->AttackList[i].current_PP_ << "/" << player_pokemon_->AttackList[i].power_points_ << std::endl;
	}
	std::cout << (i + 1) << ". Back" << std::endl;
	size_t answer = 100;

	while (answer < 1 || answer > (i+1))
	{
		std::cout << std::endl;
		std::cout << "Choice: ";
		std::cin >> answer;
	}
	if (answer == i + 1)
	{
		return;
	}
	while (player_pokemon_->AttackList[answer - 1].current_PP_ <= 0)
	{
		std::cout << std::endl;
		std::cout << "No more power points for that move!" << std::endl;
		std::cout << "Choice: ";
		std::cin >> answer;
	}
	
	player_move_ = &(player_pokemon_->AttackList[answer - 1]);
	if (std::find(player_move_->effect_.begin(), player_move_->effect_.end(), Effect::Hide) != player_move_->effect_.end() || std::find(player_move_->effect_.begin(), player_move_->effect_.end(), Effect::Charge) != player_move_->effect_.end())
	{
		player_future_move_ = player_move_;
	}
}

void Battle::OpponentChooseMove()
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(1, 100);
	int rand = distribution(generator);
	if (rand <= 30){opponent_move_ = &(opponent_pokemon_->AttackList[0]);}
	else if (rand > 30 && rand <= 60) { opponent_move_ = &(opponent_pokemon_->AttackList[1]);}
	else if (rand > 60 && rand <= 80) { opponent_move_ = &(opponent_pokemon_->AttackList[2]);}
	else { opponent_move_ = &(opponent_pokemon_->AttackList[3]);}
	
	if (std::find(opponent_move_->effect_.begin(), opponent_move_->effect_.end(), Effect::Hide) != opponent_move_->effect_.end() || std::find(opponent_move_->effect_.begin(), opponent_move_->effect_.end(), Effect::Charge) != opponent_move_->effect_.end())
	{
		opponent_future_move_ = opponent_move_;
		opponent_pokemon_->attackcounter = 0;
	}
}

//removes whatever status specified in the pokemon status vector. Might be private
void Battle::RemoveStatus(Status status, Pokemon* pokemon)
{
	for (size_t i = 0; i < pokemon->status_.size(); i++)
	{
		if (pokemon->status_[i] == Status::Charging)
		{
			pokemon->status_.erase(pokemon->status_.begin() + i);
		}
	}
	if (pokemon->status_.empty())
	{
		pokemon->status_ = { Status::Normal };
	}
}

//determine if the effect of the pokemon will impact its actual move.
bool Battle::DetermineEffect(Move* move, Pokemon* attacking, Pokemon* defending)
{
	//************************this whole group right here looks at the move to see if it needs to change the attacking pokemon's status******
	//attacks like Dig and Fly. doesn't need the remove status since it effects the visible variable
	if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Hide) != move->effect_.end()) {
		if (attacking->attackcounter == move->effect_amount_) {
			attacking->visible_ = true;
			attacking->attackcounter = 0;
			
			return true;
		}
		else if (attacking->attackcounter == 0) {
			std::cout << attacking->name_ << move->SpecialEffect << std::endl;
			attacking->visible_ = false;
			attacking->attackcounter++;
			return false;
		}
		else { return false; attacking->attackcounter++; }
	}
	//attacks like Solar Beam and Future Sight. future sight is a little special since it requires more turns to launch
	if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Charge) != move->effect_.end()) {
		if (attacking->attackcounter == move->effect_amount_) {
			attacking->attackcounter = 0;
			RemoveStatus(Status::Charging, attacking);
			return true;
		}
		else if (attacking->attackcounter == 0)
		{
			std::cout << attacking->name_ << move->SpecialEffect << std::endl;
			attacking->status_.push_back(Status::Charging);
			attacking->attackcounter++;
			return false;
		}
		else
		{
			attacking->attackcounter++;
			return true;
		}
	}
	//attacks like Fire Spin that cause excess damage
	if (std::find(move->effect_.begin(), move->effect_.end(), Effect::RepeatDamage) != move->effect_.end()) {
		if (attacking->attackcounter == move->effect_amount_) {
			attacking->attackcounter = 0;
			RemoveStatus(Status::Trapped, defending);
			return true;
		}
		else if (attacking->attackcounter == 0)
		{
			defending->status_.push_back(Status::Trapped);
			attacking->attackcounter++;
			return true;
		}
		else
		{
			attacking->attackcounter++;
			return true;
		}
	}
	if (move->name_ == "Dream Eater")
	{
		if (std::find(defending->status_.begin(), defending->status_.end(), Status::Asleep) != defending->status_.end())
		{
			return true;
		}
		else
		{
			std::cout << attacking->name_ << " used Dream Eater!" << std::endl;
			std::cout << "But it failed!" << std::endl;
			return false;
		}
	}
	//************************end of checking move*****************************************************************************
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(1, 100);
	int rand = distribution(generator);
	if (std::find(attacking->status_.begin(), attacking->status_.end(), Status::Asleep) != attacking->status_.end())
	{
		if (rand < 90 || attacking->effectcounter != 5)
		{
			std::cout << attacking->name_ << " is fast asleep." << std::endl;
			attacking->effectcounter++;
			return false;
		}
		else
		{
			std::cout << attacking->name_ << " awoke from its slumber!" << std::endl;
			RemoveStatus(Status::Frozen, attacking);
			return true;
		}
	}
	if (std::find(attacking->status_.begin(), attacking->status_.end(), Status::Confused) != attacking->status_.end())
	{
		std::cout << attacking->name_ << " is confused!" << std::endl;
		if (attacking->effectcounter == 4 || rand <= 10)
		{
			std::cout << attacking->name_ << " snapped out of confusion!" << std::endl;
			attacking->effectcounter = 0;
			RemoveStatus(Status::Confused, attacking);
			return true;
		}
		else if (rand >= 70)
		{
			std::cout << attacking->name_ << " hurt itself in its confusion!" << std::endl;
			float damage = (0.2f) * attacking->currenthealth_;
			attacking->currenthealth_ -= damage;
			attacking->effectcounter++;
			return false;
		}
		else
		{
			attacking->effectcounter++;
			return true;
		}
	}
	if (std::find(attacking->status_.begin(), attacking->status_.end(), Status::Frozen) != attacking->status_.end())
	{
		if (rand < 90)
		{
			std::cout << attacking->name_ << " is frozen solid!" << std::endl;
			return false;
		}
		else
		{
			std::cout << attacking->name_ << " defrosted itself!" << std::endl;
			RemoveStatus(Status::Frozen, attacking);
			return true;
		}
	}
	
	if (std::find(attacking->status_.begin(), attacking->status_.end(), Status::Paralyzed) != attacking->status_.end())
	{
		if (rand > 75)
		{
			std::cout << attacking->name_ << " is paralyzed! It can't move!" << std::endl;
			return false;
		}
		else
		{
			return true;
		}
	}
	return true;
}

void Battle::ExcessDamage(Pokemon* attacking)
{
	if (std::find(attacking->status_.begin(), attacking->status_.end(), Status::Poisoned) != attacking->status_.end()) {
		attacking->currenthealth_ -= (.06f * attacking->maxhealth_);
		std::cout << attacking->name_ << " was hurt from its poison!" << std::endl;
	}
	if (std::find(attacking->status_.begin(), attacking->status_.end(), Status::Fainted) != attacking->status_.end()) {
		attacking->currenthealth_ -= (.06f * attacking->maxhealth_);
		std::cout << attacking->name_ << " was hurt from its burn!" << std::endl;
	}
	if (std::find(attacking->status_.begin(), attacking->status_.end(), Status::Trapped) != attacking->status_.end()) {
		attacking->currenthealth_ -= (.06f * attacking->maxhealth_);
		std::cout << attacking->name_ << " was hurt from its burn!" << std::endl;
	}
}

//check if the moves special effect impacts the defending pokemons condition
void Battle::EndEffect(Move* move, Pokemon* attacking, Pokemon* defending)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(1, 99);
	int rand = distribution(generator);
	if (rand < move->effect_chance_)
	{
		if (std::find(move->effect_.begin(), move->effect_.end(), Effect::None) != move->effect_.end())
		{
			return;
		}
		//Atk/Def/SpAtk/SpDef/Spd effects
		if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Attack) != move->effect_.end()) {
			if (move->effect_amount_ < 0) {
				defending->attack_ += move->effect_amount_;
				std::cout << defending->name_ << "'s attack was decreased!" << std::endl;
			}
			else {
				attacking->attack_ += move->effect_amount_;
				std::cout << attacking->name_ << "'s attack was increased!" << std::endl;
			}
		}
		else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Defense) != move->effect_.end()) {
			if (move->effect_amount_ < 0) {
				defending->defense_ += move->effect_amount_;
				std::cout << defending->name_ << "'s defense was decreased!" << std::endl;
			}
			else {
				attacking->defense_ += move->effect_amount_;
				std::cout << attacking->name_ << "'s defense was increased!" << std::endl;
			}
		}
		else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Evasiveness) != move->effect_.end()) {
			if (move->effect_amount_ < 0) {
				defending->evasion_ += move->effect_amount_;
				std::cout << defending->name_ << "'s evasiveness was decreased!" << std::endl;
			}
			else {
				attacking->evasion_ += move->effect_amount_;
				std::cout << attacking->name_ << "'s evasiveness was increased!" << std::endl;
			}
		}
		else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::SpecialAttack) != move->effect_.end()) {
			if (move->effect_amount_ < 0) {
				defending->specialattack_ += move->effect_amount_;
				std::cout << defending->name_ << "'s special attack was decreased!" << std::endl;
			}
			else {
				attacking->specialattack_ += move->effect_amount_;
				std::cout << attacking->name_ << "'s special attack was increased!" << std::endl;
			}
		}
		else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::SpecialDefense) != move->effect_.end()) {
			if (move->effect_amount_ < 0) {
				defending->specialdefense_ += move->effect_amount_;
				std::cout << defending->name_ << "'s special defense was decreased!" << std::endl;
			}
			else {
				attacking->specialdefense_ += move->effect_amount_;
				std::cout << attacking->name_ << "'s special defense was increased!" << std::endl;
			}
		}
		else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Speed) != move->effect_.end()) {
			if (move->effect_amount_ < 0) {
				defending->speed_ += move->effect_amount_;
				std::cout << defending->name_ << "'s speed was decreased!" << std::endl;
			}
			else {
				attacking->speed_ += move->effect_amount_;
				std::cout << attacking->name_ << "'s speed was increased!" << std::endl;
			}
		}
		// end Stats effects ***************************************************************
		//HP effecting effects
		else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Absorb) != move->effect_.end())
		{
			float i = attacking->currenthealth_ += move->power_ * .5f;
			if (i > attacking->maxhealth_)
			{
				attacking->currenthealth_ = attacking->maxhealth_;
			}
			else
			{
				attacking->currenthealth_ = i;
			}
			std::cout << defending->name_ << move->SpecialEffect << std::endl;
		}
		else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Heal) != move->effect_.end())
		{
			float i = attacking->currenthealth_ += move->power_ * .5f;
			if (i > attacking->maxhealth_)
			{
				attacking->currenthealth_ = attacking->maxhealth_;
			}
			else
			{
				attacking->currenthealth_ = i;
			}
			std::cout << attacking->name_ << move->SpecialEffect << std::endl;
		}
		else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::KO) != move->effect_.end())
		{
			defending->currenthealth_ = 0;
			std::cout << "It's one hit KO!" << std::endl;
		}
		else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::RepeatDamage) != move->effect_.end())
		{
			
		}
		//***********end HP effects*************************************************************
		//*****************defending pokemon condition effects*********************************
		else 
		{
			Status condition;
			std::string declaration;
			if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Confuse) != move->effect_.end())	{
				condition = Status::Confused;
				declaration = " confused";
			}
			else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Burn) != move->effect_.end()) {
				condition = Status::Fainted;
				declaration = " Fainted";
			}
			else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Paralyze) != move->effect_.end()) {
				condition = Status::Paralyzed;
				declaration = " paralyzed";
			}
			else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Freeze) != move->effect_.end()) {
				condition = Status::Frozen;
				declaration = " frozen";
			}
			else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Poison) != move->effect_.end()) {
				condition = Status::Poisoned;
				declaration = " poisoned";
			}
			else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Burn) != move->effect_.end()) {
				condition = Status::Fainted;
				declaration = " Fainted";
			}
			else if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Sleep) != move->effect_.end()) {
				condition = Status::Asleep;
				declaration = " asleep";
			}
			else {
				return;
			}

			if (std::find(defending->status_.begin(), defending->status_.end(), condition) != defending->status_.end())
			{
				std::cout << defending->name_ << " is already" << declaration << "!" << std::endl;
			}
			else if ((std::find(defending->status_.begin(), defending->status_.end(), Status::Asleep) != defending->status_.end()) || !defending->visible_)
			{
				if (move->category_ == MoveCategory::Status)
				{
					std::cout << "But it failed!" << std::endl;
				}
				else
				{
					return;
				}
			}
			else
			{
				RemoveStatus(Status::Normal, defending);
				defending->status_.push_back(condition);
				std::cout << defending->name_ << " is" << declaration << "!" << std::endl;
			}
		}
	}
	else
	{
		return;
	}
}

bool Battle::CheckIfHit(Move* move, Pokemon* defending)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(1, 100);
	int rand = distribution(generator);

	if (((rand > (move->accuracy_ - defending->evasion_)) && (move->category_ != MoveCategory::Status)) || (defending->visible_ == false))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Battle::UseMove(Move* move, Pokemon* attacking, Pokemon* defending)
{
	//if (std::find(move->effect_.begin(), move->effect_.end(), Effect::Hide) != move->effect_.end() || std::find(move->effect_.begin(), move->effect_.end(), Effect::Charge) != move->effect_.end())
	//{
	//	attacking->future_move_ = move;
	//}
	float modifier = CalculateModifier(move, defending);
	if (DetermineEffect(move, attacking, defending))
	{
		move->current_PP_ -= 1;
		std::cout << attacking->name_ << " used " << move->name_ << "!" << std::endl;
		if (CheckIfHit(move, defending) || move->category_ == MoveCategory::Status)
		{
		
			float damage = CalculateDamage(move, attacking, defending) * modifier;
			if (move->category_ == MoveCategory::Status && move->effect_amount_ > 0)
			{
				//this shouldn't say anything. Status moves don't miss or gets any super/not very/doesn't effect shit
			}
			else if (modifier >= 2)
			{
				std::cout << "It's super effective!" << std::endl;
			}
			else if (modifier == 0)
			{
				std::cout << "It doesn't effect " << defending->name_ << "..." << std::endl;
			}
			else if (modifier > 0.0f && modifier < 1.0f)
			{
				std::cout << "It's not very effective..." << std::endl;
			}
			defending->currenthealth_ -= damage;
			if (modifier != 0)
			{
				EndEffect(move, attacking, defending);
			}
		}
		else {
			std::cout << "The attack missed!" << std::endl;
		}
	}
	
	ExcessDamage(attacking);
	
}

//damage calculations******************************************************
float Battle::CalculateModifier(Move* move, Pokemon* defending)
{
	Type attacktype = move->type_;
	std::vector<Type> weaklist = defending->PrimaryWeakToList;
	std::vector<Type> resistancelist = defending->PrimaryResistantToList;
	std::vector<Type> immunelist = defending->PrimaryImmuneToList;
	std::vector<Type> weaklist2 = defending->SecondaryWeakToList;
	std::vector<Type> resistancelist2 = defending->SecondaryResistantToList;
	std::vector<Type> immunelist2 = defending->SecondaryImmuneToList;
	float p;
	float s;
	if (std::find(weaklist.begin(), weaklist.end(), attacktype) != weaklist.end())
	{
		p = 2;
	}
	else if (std::find(resistancelist.begin(), resistancelist.end(), attacktype) != resistancelist.end())
	{
		p = 0.5;
	}
	else if (std::find(immunelist.begin(), immunelist.end(), attacktype) != immunelist.end())
	{
		p = 0;
	}
	else
	{
		p = 1;
	}
	if (std::find(weaklist2.begin(), weaklist2.end(), attacktype) != weaklist2.end())
	{
		s = 2;
	}
	else if (std::find(resistancelist2.begin(), resistancelist2.end(), attacktype) != resistancelist2.end())
	{
		s = 0.5;
	}
	else if (std::find(immunelist2.begin(), immunelist2.end(), attacktype) != immunelist2.end())
	{
		s = 0;
	}
	else
	{
		s = 1;
	}
	return (p * s);
}
float Battle::CalculateDamage(Move* move, Pokemon* attacking, Pokemon* defending)
{
	float a = (2.0f * attacking->level_) / 5.0f;
	float b;
	if (move == nullptr)
	{
		return 0;
	}
	if (move->category_ == MoveCategory::Physical)
	{
		b = attacking->attack_ / defending->defense_;
	}
	else if (move->category_ == MoveCategory::Special)
	{
		b = attacking->specialattack_ / defending->specialdefense_;
	}
	else
	{
		b = attacking->attack_ / defending->defense_;
	}
	float damage = ((a * move->power_ * b) / 50);
	return damage;
}
//end damage calculations*****************************************************

//*********************items**************************************
void Battle::ChooseItem()
{
	size_t answer = 100;
	size_t answer2 = 100;
	size_t pokemons = 0;
	std::vector<Item*> items = {};
	while (true)
	{
		std::cout << "Choose an item: " << std::endl;
		int itemnumber = 1;
		for (size_t i = 0; i < player_->items_.size(); i++)
		{
			std::cout << itemnumber << ". " << player_->items_[i].name_;
			items.push_back(&(player_->items_[i]));
			size_t additionalcheck = 1;
			int additionalitems = 1;
			int n = i;
			for (additionalcheck; additionalcheck < (player_->items_.size()-n); additionalcheck++)
			{
				if (player_->items_[n + additionalcheck].name_ == player_->items_[n].name_)
				{
					additionalitems++;
					i++;
				}
				
			}
			if (additionalitems > 1)
			{
				std::cout << " x" << additionalitems << std::endl;
			}
			else
			{
				std::cout << std::endl;
			}
			itemnumber++;
		}
		std::cout << itemnumber << ". Back" << std::endl;

		std::cout << "Choice: ";
		std::cin >> answer;

		if (answer == itemnumber)
		{
			player_item_ = nullptr;
			break;
		}
		else {
			player_item_ = items[answer - 1];

			while (true)
			{
				if (player_item_pokemon != nullptr || answer2 == pokemons + 1)
				{
					answer2 = 100;
					break;
				}
				std::cout << "Which pokemon would you like to use " << player_item_->name_ << " on?" << std::endl;
				answer2 = 100;
				pokemons = 0;
				for (pokemons; pokemons < player_pokemons_->size(); pokemons++)
				{
					std::cout << (pokemons + 1) << ". " << player_pokemons_->at(pokemons).name_ << std::endl;
				}
				std::cout << pokemons + 1 << ". Back" << std::endl;


				while (true)
				{

					while (answer2 > (pokemons + 1) || answer2 < 0)
					{
						std::cout << "Choice: ";
						std::cin >> answer2;

					}
					if (answer2 == pokemons + 1)
					{
						answer = 100;
						player_item_ = nullptr;
						break;
					}
					else if (player_item_->type_ == ItemType::CureConfusion && std::find(player_pokemons_->at(answer2 - 1).status_.begin(), player_pokemons_->at(answer2 - 1).status_.end(), Status::Confused) == player_pokemons_->at(answer2 - 1).status_.end())
					{
						std::cout << "This pokemon is not confused!" << std::endl;
						answer = 100;
						break;
					}
					else if (player_item_->type_ == ItemType::CureBurn && std::find(player_pokemons_->at(answer2 - 1).status_.begin(), player_pokemons_->at(answer2 - 1).status_.end(), Status::Burned) == player_pokemons_->at(answer2 - 1).status_.end())
					{
						std::cout << "This pokemon is not burned!" << std::endl;
						answer = 100;
						break;
					}
					else if (player_item_->type_ == ItemType::CureParalysis && std::find(player_pokemons_->at(answer2 - 1).status_.begin(), player_pokemons_->at(answer2 - 1).status_.end(), Status::Paralyzed) == player_pokemons_->at(answer2 - 1).status_.end())
					{
						std::cout << "This pokemon is not confused!" << std::endl;
						answer = 100;
						break;
					}
					else if (player_item_->type_ == ItemType::CurePoison && std::find(player_pokemons_->at(answer2 - 1).status_.begin(), player_pokemons_->at(answer2 - 1).status_.end(), Status::Poisoned) == player_pokemons_->at(answer2 - 1).status_.end())
					{
						std::cout << "This pokemon is not confused!" << std::endl;
						answer = 100;
						break;
					}
					else if (player_item_->type_ == ItemType::Defrost && std::find(player_pokemons_->at(answer2 - 1).status_.begin(), player_pokemons_->at(answer2 - 1).status_.end(), Status::Frozen) == player_pokemons_->at(answer2 - 1).status_.end())
					{
						std::cout << "This pokemon is not frozen!" << std::endl;
						answer = 100;
						break;
					}
					else if (player_item_->type_ == ItemType::Wake && std::find(player_pokemons_->at(answer2 - 1).status_.begin(), player_pokemons_->at(answer2 - 1).status_.end(), Status::Asleep) == player_pokemons_->at(answer2 - 1).status_.end())
					{
						std::cout << "This pokemon is not asleep!" << std::endl;
						answer = 100;
						break;
					}
					else if (player_item_->type_ == ItemType::Revive && std::find(player_pokemons_->at(answer2 - 1).status_.begin(), player_pokemons_->at(answer2 - 1).status_.end(), Status::Fainted) == player_pokemons_->at(answer2 - 1).status_.end())
					{
						std::cout << "This pokemon is not fainted!" << std::endl;
						answer = 100;
						break;
					}
					else
					{
						player_item_pokemon = &(player_pokemons_->at(answer2 - 1));
						break;
					}
				}
				if (player_item_pokemon != nullptr)
				{
					break;
				}
			}
		}
		if (player_item_pokemon != nullptr)
		{
			break;
		}
	}
	
}

void Battle::UseItem(Item* item, Trainer* trainer, Pokemon* pokemon)
{
	
	if (item->type_ == ItemType::Attack)
	{
		pokemon->attack_ += item->power_;
		std::cout << pokemon->name_ << "'s attack increased!" << std::endl;
	}
	else if (item->type_ == ItemType::CureBurn)
	{
		if (std::find(pokemon->status_.begin(), pokemon->status_.end(), Status::Burned) != pokemon->status_.end())
		{
			for (size_t i = 0; i < pokemon->status_.size(); i++)
			{
				if (pokemon->status_[i] == Status::Burned)
				{
					pokemon->status_.erase(pokemon->status_.begin() + i);
				}
			}
			if (pokemon->status_.empty())
			{
				pokemon->status_ = { Status::Normal };
			}
		}
		else
		{
			std::cout << pokemon->name_ << "is not burned!" << std::endl;
		}

	}
	else if (item->type_ == ItemType::CureConfusion)
	{
		if (std::find(pokemon->status_.begin(), pokemon->status_.end(), Status::Confused) != pokemon->status_.end())
		{
			for (size_t i = 0; i < pokemon->status_.size(); i++)
			{
				if (pokemon->status_[i] == Status::Confused)
				{
					pokemon->status_.erase(pokemon->status_.begin() + i);
				}
			}
			if (pokemon->status_.empty())
			{
				pokemon->status_ = { Status::Normal };
			}
		}
		else
		{
			std::cout << pokemon->name_ << "is not confused!" << std::endl;
		}
	}
	else if (item->type_ == ItemType::CureParalysis)
	{
		if (std::find(pokemon->status_.begin(), pokemon->status_.end(), Status::Paralyzed) != pokemon->status_.end())
		{
			for (size_t i = 0; i < pokemon->status_.size(); i++)
			{
				if (pokemon->status_[i] == Status::Paralyzed)
				{
					pokemon->status_.erase(pokemon->status_.begin() + i);
				}
			}
			if (pokemon->status_.empty())
			{
				pokemon->status_ = { Status::Normal };
			}
		}
		else
		{
			std::cout << pokemon->name_ << "is not paralyzed!" << std::endl;
		}
	}
	else if (item->type_ == ItemType::CurePoison)
	{
		if (std::find(pokemon->status_.begin(), pokemon->status_.end(), Status::Poisoned) != pokemon->status_.end())
		{
			for (size_t i = 0; i < pokemon->status_.size(); i++)
			{
				if (pokemon->status_[i] == Status::Poisoned)
				{
					pokemon->status_.erase(pokemon->status_.begin() + i);
				}
			}
			if (pokemon->status_.empty())
			{
				pokemon->status_ = { Status::Normal };
			}
		}
		else
		{
			std::cout << pokemon->name_ << "is not poisoned!" << std::endl;
		}
	}
	else if (item->type_ == ItemType::Defense)
	{
		pokemon->defense_ += item->power_;
		std::cout << pokemon->name_ << "'s defense increased!" << std::endl;
	}
	else if (item->type_ == ItemType::Defrost)
	{
		if (std::find(pokemon->status_.begin(), pokemon->status_.end(), Status::Frozen) != pokemon->status_.end())
		{
			for (size_t i = 0; i < pokemon->status_.size(); i++)
			{
				if (pokemon->status_[i] == Status::Frozen)
				{
					pokemon->status_.erase(pokemon->status_.begin() + i);
				}
			}
			if (pokemon->status_.empty())
			{
				pokemon->status_ = { Status::Normal };
			}
		}
		else
		{
			std::cout << pokemon->name_ << "is not frozen!" << std::endl;
		}
	}
	else if (item->type_ == ItemType::RestoreHP)
	{
		if (pokemon->currenthealth_ != pokemon->maxhealth_)
		{
			if (pokemon->currenthealth_ += item->power_ > pokemon->maxhealth_)
			{
				pokemon->currenthealth_ = pokemon->maxhealth_;

			}
			else
			{
				pokemon->currenthealth_ += item->power_;
			}
			std::cout << pokemon->name_ << "'s health has been restored." << std::endl;
		}
		else
		{
			std::cout << pokemon->name_ << "'s health is already full!" << std::endl;
		}
	}
	else if (item->type_ == ItemType::Revive)
	{
		if (std::find(pokemon->status_.begin(), pokemon->status_.end(), Status::Fainted) != pokemon->status_.end())
		{
			for (size_t i = 0; i < pokemon->status_.size(); i++)
			{
				if (pokemon->status_[i] == Status::Fainted)
				{
					pokemon->status_.erase(pokemon->status_.begin() + i);
				}
			}
			std::cout << pokemon->name_ << " has been revived!" << std::endl;
			pokemon->status_ = { Status::Normal };
			
		}
		else
		{
			std::cout << pokemon->name_ << "is not Fainted!" << std::endl;
		}
	}
	else if (item->type_ == ItemType::SpecialAttack)
	{
		pokemon->specialattack_ += item->power_;
		std::cout << pokemon->name_ << "'s special attack increased!" << std::endl;
	}
	else if (item->type_ == ItemType::SpecialDefense)
	{
		pokemon->specialdefense_ += item->power_;
		std::cout << pokemon->name_ << "'s special defense increased!" << std::endl;
	}
	else if (item->type_ == ItemType::Speed)
	{
		pokemon->speed_ += item->power_;
		std::cout << pokemon->name_ << "'s speed increased!" << std::endl;
	}
	else if (item->type_ == ItemType::Wake)
	{
	if (std::find(pokemon->status_.begin(), pokemon->status_.end(), Status::Asleep) != pokemon->status_.end())
	{
		for (size_t i = 0; i < pokemon->status_.size(); i++)
		{
			if (pokemon->status_[i] == Status::Asleep)
			{
				pokemon->status_.erase(pokemon->status_.begin() + i);
			}
		}
		if (pokemon->status_.empty())
		{
			pokemon->status_ = { Status::Normal };
		}
		std::cout << pokemon->name_ << " has been awakened!" << std::endl;
	}
	else
	{
		std::cout << pokemon->name_ << "is not asleep!" << std::endl;
	}
	}

	for (size_t i = 0; i < trainer->items_.size(); i++)
	{
		if (item->name_ == trainer->items_[i].name_)
		{
			trainer->items_.erase(trainer->items_.begin() + i);
			break;
		}
	}
}

void Battle::OpponentChooseItem()
{
	if (opponent_pokemon_->currenthealth_ > (opponent_pokemon_->maxhealth_) * .25f)
	{
		opponent_item = &(opponent_->items_[0]);
	}
	else if (std::find(opponent_pokemon_->status_.begin(), opponent_pokemon_->status_.end(), Status::Confused) != opponent_pokemon_->status_.end())
	{
		opponent_item = &(opponent_->items_[1]);
	}
	else if (std::find(opponent_pokemon_->status_.begin(), opponent_pokemon_->status_.end(), Status::Paralyzed) != opponent_pokemon_->status_.end())
	{
		opponent_item = &(opponent_->items_[2]);
	}
	else if (std::find(opponent_pokemon_->status_.begin(), opponent_pokemon_->status_.end(), Status::Burned) != opponent_pokemon_->status_.end())
	{
		opponent_item = &(opponent_->items_[3]);
	}
	else if (std::find(opponent_pokemon_->status_.begin(), opponent_pokemon_->status_.end(), Status::Frozen) != opponent_pokemon_->status_.end())
	{
		opponent_item = &(opponent_->items_[4]);
	}
	else if (std::find(opponent_pokemon_->status_.begin(), opponent_pokemon_->status_.end(), Status::Poisoned) != opponent_pokemon_->status_.end())
	{
		opponent_item = &(opponent_->items_[5]);
	}
	else if (std::find(opponent_pokemon_->status_.begin(), opponent_pokemon_->status_.end(), Status::Asleep) != opponent_pokemon_->status_.end())
	{
		opponent_item = &(opponent_->items_[6]);
	}
}