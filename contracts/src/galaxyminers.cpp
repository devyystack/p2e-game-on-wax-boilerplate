// #include <galaxyminers.hpp>
// ACTION galaxyminers::hi( name nm ) {
//    /* fill in action body */
//    print_f("Name : %\n",nm);
// }


#include <galaxyminers.hpp>
#include <atomicassets-interface.hpp>
#include "../utils/utils.cpp"
#include <eosio/crypto.hpp>
#include <eosio/time.hpp>
#include <eosio/system.hpp>

inline void verify_sha256_prefix(const std::string &value, const std::string &compared_hash)
{
  auto hash = eosio::sha256(value.c_str(), value.length());
  auto arr = hash.extract_as_byte_array();

  const char *hex_characters = "0123456789abcdef";
  std::string hash_prefix;
  const uint8_t *d = reinterpret_cast<const uint8_t *>(arr.data());

  auto prefix_size = compared_hash.length() / 2;
  for (uint32_t i = 0; i < prefix_size; ++i)
  {
    hash_prefix += hex_characters[d[i] >> 4];
    hash_prefix += hex_characters[d[i] & 0x0f];
  }

  eosio::check(compared_hash == hash_prefix,
               "fail to verify hash: " + compared_hash + " should be " + hash_prefix);
}

void nicegm::managewl(eosio::name owner, bool is_active)
{

  require_auth(get_self());

  // Check if this user was created before
  whitelist user(_self, _self.value);

  auto iter = user.find(owner.value);

  if (iter == user.end()) {
    // creates new user
    user.emplace(_self, [&](auto &u)
                      {
                        u.account = owner;
                        u.is_active = is_active;
                      });
  } else {
    user.modify(iter, _self, [&](auto &p){
      p.is_active = is_active;
    });
  }
}

void nicegm::addplayer(eosio::name owner, eosio::name referral_partner)
{

  // Check if community was created before
  players user(_self, _self.value);

  auto iter = user.find(owner.value);

  if (iter == user.end()) {
    require_auth(owner);
    require_recipient(owner);
    // creates new user
    user.emplace(_self, [&](auto &u)
                      {
                        u.account = owner;
                        u.energy = 500;
                        u.max_energy = 1500;
                        u.last_mine_tx = (eosio::checksum256&)"0000000000000000000000000000000000000000000000000000000000000000";// eosio::sha256("0", 64);// 
                        u.balances =  std::vector<eosio::asset>();
                      });
  } else {
    // require_auth(get_self());
    // std::vector<eosio::asset> temp;
    // auto sym_asteroid = eosio::symbol("ASTEROI", 4); 
    // auto sym_plasma = eosio::symbol("PLASMA", 4); 
    // auto sym_oxygen = eosio::symbol("OXYGEN", 4); 
    // temp.push_back(eosio::asset{10000000, sym_asteroid});
    // temp.push_back(eosio::asset{10000000, sym_plasma});
    // temp.push_back(eosio::asset{10000000, sym_oxygen});

    // user.modify(iter, _self, [&](auto &p){
    //   p.balances = temp;
    // });
  }

}

void nicegm::addconfitem(std::string schema_name, template_id_type template_id, std::string name, std::string img, bool can_burn) {
  require_auth(get_self());

  configitem item(_self, _self.value);

  item.emplace(_self, [&](auto &i)
                      {
                        i.schema_name = schema_name;
                        i.template_id = template_id;
                        i.name = name;
                        i.img = img;
                        i.can_burn = can_burn;
                      }
              );
}

void nicegm::delconfitem(template_id_type template_id) {

  require_auth(get_self());

  // do something here to remove items
}

void nicegm::addsetting(energy_type init_energy, energy_type init_max_energy, uint32_t reward_noise_min, uint32_t reward_noise_max, std::uint8_t min_fee, std::uint8_t max_fee, std::uint8_t fee) {
  require_auth(get_self());
  setting item(_self, _self.value);

  auto it = item.begin();
  if (it == item.end()) { // inserting newly
    item.emplace(_self, [&](auto &c)
                  {
                    c.init_energy = init_energy;
                    c.init_max_energy = init_max_energy;
                    c.reward_noise_min = reward_noise_min;
                    c.reward_noise_max = reward_noise_max;
                    c.min_fee = min_fee;
                    c.max_fee = max_fee;
                    c.last_fee_updated = now();
                    c.fee = fee;
                  }
  );
  } else {
    item.modify(it, _self, [&](auto &c){
      c.init_energy = init_energy;
      c.init_max_energy = init_max_energy;
      c.reward_noise_min = reward_noise_min;
      // c.reward_noise_max = reward_noise_max;  // temporarily commented as it is set as primary key
      c.min_fee = min_fee;
      c.max_fee = max_fee;
      c.last_fee_updated = now();
      c.fee = fee;
    });
  }
}

void nicegm::delsetting() {

  require_auth(get_self());

  // do something here
}

void nicegm::addconfbadge(std::string name, std::uint32_t template_id, std::string type, std::string img, std::string badge_img, std::uint8_t saved_claims, std::uint8_t additional_slots, std::uint16_t additional_energy, std::uint8_t rewards_rate, std::uint8_t lucky, eosio::asset plasmas_mint, std::uint16_t coins_mint, std::uint64_t unstaking_time, std::uint64_t charged_time) {
  
  require_auth(get_self());

  configbadge item(_self, _self.value);

  item.emplace(_self, [&](auto &i)
                      {
                        i.name = name;
                        i.template_id = template_id;
                        i.type = type;
                        i.img = img;
                        i.badge_img = badge_img;
                        i.saved_claims = saved_claims;
                        i.additional_slots = additional_slots;
                        i.additional_energy = additional_energy;
                        i.rewards_rate = rewards_rate;
                        i.lucky = lucky;
                        i.plasmas_mint = plasmas_mint;
                        i.coins_mint = coins_mint;
                        i.unstaking_time = unstaking_time;
                        i.charged_time = charged_time;
                      }
              );
}

void nicegm::delconfbadge(std::uint32_t template_id) {

  require_auth(get_self());

  // do something here to remove items
}

void nicegm::addbcraft(std:: uint32_t id, std::string name, std::string img, std::uint8_t saved_claims, std::uint8_t additional_slots, std::uint16_t additional_energy, std::uint8_t rewards_rate, std::uint8_t lucky, eosio::asset plasmas_mint, std::uint16_t coins_mint, std::uint64_t unstaking_time, std::uint64_t charged_time) {

  require_auth(get_self());

  badgecraft item(_self, _self.value);

  item.emplace(_self, [&](auto &i)
                      {
                        i.id = id;
                        i.name = name;
                        i.img = img;
                        i.saved_claims = saved_claims;
                        i.additional_slots = additional_slots;
                        i.additional_energy = additional_energy;
                        i.rewards_rate = rewards_rate;
                        i.lucky = lucky;
                        i.plasmas_mint = plasmas_mint;
                        i.coins_mint = coins_mint;
                        i.unstaking_time = unstaking_time;
                        i.charged_time = charged_time;
                      }
              );
}

void nicegm::addconftool(std::string template_name, std::string img,
eosio::name schema_name, eosio::name owner, std::string type, std::string rarity, std::uint8_t level, template_id_type template_id, energy_type energy_consumed, durability_type durability_consumed, std::vector<eosio::asset> mints, std::vector<eosio::asset> rewards, std::uint32_t charged_time) {

  require_auth(get_self());
  // require_auth(owner);

  configtools item(_self, _self.value);

  auto current_item = item.find(string_to_uint64_t(img));
  if (current_item == item.end()) { // inserting newly
    item.emplace(_self, [&](auto &i)
                        {
                          i.template_name = template_name;
                          i.img = img;
                          i.schema_name = schema_name;
                          i.type = type;
                          i.rarity = rarity;
                          i.level = level;
                          i.template_id = template_id;
                          i.energy_consumed = energy_consumed;
                          i.durability_consumed = durability_consumed;
                          i.mints = mints;
                          i.rewards = rewards;
                          i.charged_time = charged_time;
                        }
                );
  } else {
    item.modify(current_item, _self, [&](auto &i){
      i.template_name = template_name;
      i.img = img;
      i.schema_name = schema_name;
      i.type = type;
      i.rarity = rarity;
      i.level = level;
      i.template_id = template_id;
      i.energy_consumed = energy_consumed;
      i.durability_consumed = durability_consumed;
      i.mints = mints;
      i.rewards = rewards;
      i.charged_time = charged_time;
    });
  }

}

void nicegm::addgadget(asset_id_type asset_id, eosio::name owner, std::string type, template_id_type template_id, durability_type durability, durability_type current_durability, std::uint64_t next_availability)
{
  eosio::check(false, "This function is closed!");

  require_auth(owner);

  // // check if this user is in whitelist_table
  // whitelist wluser(_self, _self.value);
  // auto wlu = wluser.find(owner.value);
  // eosio::check(wlu != wluser.end(), "Can't use this function for now!!");
  // eosio::check(wlu->is_active == true, "Can't use this function for now!!");
  // // end of checking

  // creates new gadget
  gadgets gadget(_self, _self.value);

  auto tool_durability = 0;
  switch (template_id) {
      case 446583: tool_durability = 200; break; // Oxygen Jar
      case 446585: tool_durability = 3500; break; // Oxygen Tank
      case 446584: tool_durability = 1400; break; // Oxygen Backpack

      case 411903: tool_durability = 2550; break; // Asteroid Drone
      case 411902: tool_durability = 600; break; // 	Asteroid Dissolver
      case 411906: tool_durability = 100; break; // Asteroid Scanner
      case 438433: tool_durability = 250; break; // 	Asteroid Clever

      case 411924: tool_durability = 2500; break; // 	Plasma Ionizer
      case 411923: tool_durability = 250; break; // Plasma Collector
      default: eosio::check(false, "Wrong template id"); break;
  }
  if (tool_durability == 0) {
    tool_durability = durability;
  }
  gadget.emplace(_self, [&](auto &g)
                    {
                      g.asset_id = asset_id;
                      g.owner = owner;
                      g.type = type;
                      g.template_id = template_id;
                      g.durability = tool_durability;
                      g.current_durability = tool_durability;
                      g.next_availability = next_availability;
                    });

  // Notify owner
  require_recipient(owner);
}

void nicegm::detachgadget(asset_id_type asset_id, eosio::name owner)
{

  require_auth(owner);

  // // check if this user is in whitelist_table
  // whitelist wluser(_self, _self.value);
  // auto wlu = wluser.find(owner.value);
  // eosio::check(wlu != wluser.end(), "Can't use this function for now!!");
  // eosio::check(wlu->is_active == true, "Can't use this function for now!!");
  // // end of checking

  // check if this user have 500 energy at least to unstake
  players player(_self, _self.value);

  auto iter = player.find(owner.value);

  gadgets gadget(_self, _self.value);
  auto current_gadget = gadget.find(asset_id);
  eosio::check(current_gadget != gadget.end(), "Not found gadget");
  eosio::check(current_gadget->owner == owner, "You can't detach other's tool!");
  eosio::check(current_gadget->durability == current_gadget->current_durability, "Not enough durability!");
  eosio::check(current_gadget->next_availability < now(), "Countdown is not finished yet");

  
  eosio::check(iter != player.end(), "Not found player");
  eosio::check(iter->energy >= 500, "No enough energy");

  // player.modify(iter, _self, [&](auto &p){
  //   p.energy = p.energy - 500;
  // });
  // end of check

  std::vector<asset_id_type> arr_item;
  arr_item.push_back(asset_id);
  // // transfer NFT using deferred transaction
  // auto transfer_id = gen_uuid(owner.value + now(), owner.value + now());
  // eosio::transaction trx{};
  // trx.actions.emplace_back(eosio::permission_level{get_self(), eosio::name{"active"}}, // Permission
  //                           eosio::name{"atomicassets"},                                                 // Account
  //                           eosio::name{"transfer"},                                      // Action
  //                           std::make_tuple(get_self(), owner, arr_item, std::string("unstake")));
  // // trx.delay_sec = the_period; // uint32_t
  // trx.send(transfer_id, get_self(), true);

  // transfer NFT uisng action
  eosio::action(eosio::permission_level{get_self(), eosio::name{"active"}}, // Permission
                eosio::name{"atomicassets"},                                                 // Account
                eosio::name{"transfer"},                                      // Action
                std::make_tuple(get_self(), owner, arr_item, std::string("unstake"))
    ).send();

  gadget.erase(current_gadget);
}

void nicegm::on_transfer(eosio::name from,eosio::name to, std::vector<uint64_t> asset_ids, std::string memo) {

  if (memo == "openpack") {
    // Check for legitimate transfer
    eosio::check(from != _self && to == _self, "Wrong data!");

    // Burn Em' All!
    // for (auto it = asset_ids.begin(); it != asset_ids.end(); it++)
    for (uint64_t asset_id : asset_ids)
    {
      // nicegm::assets_t owner_assets = get_assets(_self);
      
      // auto asset_itr = owner_assets.require_find(asset_id, ("Sender doesn't own at least one of the provided assets (ID: " +
      //        to_string(asset_id) + ")").c_str());
      // if (asset_itr->template_id >= 0) {
        // burning
        eosio::action(eosio::permission_level{get_self(), eosio::name{"active"}}, // Permission
                      eosio::name{"atomicassets"},                                // Account
                      eosio::name{"burnasset"},                                   // Action
                      std::make_tuple(_self, asset_id)
          ).send();

        // adding game resource to this user
        players player(_self, _self.value);
        auto iter = player.find(from.value);
        eosio::check(iter != player.end(), "Not found player");
        
        auto sym_asteroid = eosio::symbol("ASTEROI", 4);
        auto sym_plasma = eosio::symbol("PLASMA", 4);
        auto sym_oxygen = eosio::symbol("OXYGEN", 4);
        eosio::asset current_asset;

        if (asset_id <= 1099665142465 && asset_id >= 1099665137968) {
          current_asset = eosio::asset{2000000, sym_asteroid};
        } else if (asset_id <= 1099665146170 && asset_id >= 1099665144231) {
          current_asset = eosio::asset{2000000, sym_oxygen};
        } else if (asset_id <= 1099665137577 && asset_id >= 1099665132660) {
          current_asset = eosio::asset{1000000, sym_plasma};
        } else {
          eosio::check(2 > 3, "Wrong pack name!");
        }
        
        player.modify(iter, _self, [&](auto &p){

          std::vector<eosio::asset> temp;

          bool is_used = false;
          for (auto balance = p.balances.begin(); balance != p.balances.end(); balance++) {
            if (balance->symbol == current_asset.symbol) {
              balance->amount += current_asset.amount;
              temp.push_back(eosio::asset{balance->amount, balance->symbol});
              is_used = true;
            } else {
              temp.push_back(eosio::asset{balance->amount, balance->symbol});
            }
          }
          if (is_used == false) {
              temp.push_back(current_asset);
          }

          p.balances = temp;
          // p.last_mine_tx = now();
        });
        
      // }
    }
  } else {
    // require_auth(from);

    std::string type44;
    std::uint64_t template_id;

    std::string delimiter = "--";
    std::uint8_t pos = 0;

    pos = memo.find(delimiter);
    // eosio::check(false, to_string(pos));
    if (pos != 255) {
      type44 = memo.substr(0, pos);
      memo.erase(0, pos + delimiter.length());
      template_id = std::stoi(memo);

    
      // template_id = std::stoi(memo.substr(2, memo.find(delimiter)));
      // if (memo == "stakePlasma") {
      //   type = "Plasma";
      // } else if (memo == "stakeOxygen") {
      //   type = "Oxygen";
      // } else if (memo == "stakeAsteroid") {
      //   type = "Asteroid";
      // }

      // template_id = asset_ids[1];
      // asset_id = asset_ids[0];

      // creates new gadget
      gadgets gadget(_self, _self.value);

      auto tool_durability = 0;

      switch (template_id) {
          case 446583: tool_durability = 200; break; // Oxygen Jar
          case 446585: tool_durability = 3500; break; // Oxygen Tank
          case 446584: tool_durability = 1400; break; // Oxygen Backpack

          case 411903: tool_durability = 2550; break; // Asteroid Drone
          case 411902: tool_durability = 600; break; // 	Asteroid Dissolver
          case 411906: tool_durability = 100; break; // Asteroid Scanner
          case 438433: tool_durability = 250; break; // 	Asteroid Clever

          case 411924: tool_durability = 2500; break; // 	Plasma Ionizer
          case 411923: tool_durability = 250; break; // Plasma Collector
          default: eosio::check(false, "Wrong template id"); break;
      }
      for (uint64_t asset_id : asset_ids) {
        gadget.emplace(_self, [&](auto &g)
                          {
                            g.asset_id = asset_id;
                            g.owner = from;
                            g.type = type44;
                            g.template_id = template_id;
                            g.durability = tool_durability;
                            g.current_durability = tool_durability;
                            g.next_availability = 0;
                          });
      }
    }
  }
}

void nicegm::claim(eosio::name asset_owner, asset_id_type asset_id, std::string img)
{

  require_auth(asset_owner);

  // // check if this user is in whitelist_table
  // whitelist wluser(_self, _self.value);
  // auto wlu = wluser.find(asset_owner.value);
  // eosio::check(wlu != wluser.end(), "Can't use this function for now!!");
  // eosio::check(wlu->is_active == true, "Can't use this function for now!!");
  // // end of checking

  players player(_self, _self.value);
  gadgets gadget(_self, _self.value);
  configtools configtool(_self, _self.value);

  auto ct = configtool.find(string_to_uint64_t(img));
  auto iter = player.find(asset_owner.value);
  auto current_gadget = gadget.find(asset_id);
  
  eosio::check(ct != configtool.end(), "Not found configtool");
  eosio::check(iter != player.end(), "Not found player");
  eosio::check(current_gadget != gadget.end(), "Not found gadget");
  eosio::check(iter->energy - ct->energy_consumed > 0, "No enough energy");
  eosio::check(current_gadget->current_durability - ct->durability_consumed > 0, "No enough durability");
  eosio::check(current_gadget->next_availability < now(), "Countdown is not finished yet");

  
  gadget.modify(current_gadget, _self, [&](auto &g){
    g.current_durability = g.current_durability - ct->durability_consumed;
    // auto nowWithMicroseconds = time_point(current_time())
    // auto nowWithSeconds = eosio::time_point_sec(now()) + ct->charged_time;
    auto nowWithSeconds = now() + ct->charged_time;
    g.next_availability = nowWithSeconds;
  });


  player.modify(iter, _self, [&](auto &p){
    // calc rewards
    auto rewards = ct->rewards;
    std::vector<eosio::asset> temp;
    for (auto reward = rewards.begin(); reward != rewards.end(); reward++) {
      bool is_used = false;
      for (auto balance = p.balances.begin(); balance != p.balances.end(); balance++) {
        if (reward->symbol == balance->symbol) {
          balance->amount += reward->amount;
          temp.push_back(eosio::asset{balance->amount, balance->symbol});
          is_used = true;
          break;
        }
      }
      if (is_used == false) {
          temp.push_back(eosio::asset{reward->amount, reward->symbol});
      }
    }

    for (auto balance = p.balances.begin(); balance != p.balances.end(); balance++) {
      bool is_used = false;
      for (auto reward = rewards.begin(); reward != rewards.end(); reward++) {
        if (reward->symbol == balance->symbol) {
          is_used = true;
          break;
        }
      }
      if (is_used == false) {
          temp.push_back(eosio::asset{balance->amount, balance->symbol});
      }
    }

    p.balances = temp;
    p.energy -= ct->energy_consumed;
    // p.last_mine_tx = now();
  });

  ///////////////////////////////////////////RESET//////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // // modify configtools data for this img
  // configtool.modify(ct, _self, [&](auto &g){
  //   g.charged_time = 60;
  // });
  // // delete all data in a table
  // auto it = gadget.begin();
  // while (it != gadget.end()) {
  //     it = gadget.erase(it);
  // }

  // // reset all data in players table
  // auto itp = player.begin();
  // while (itp != player.end()) {
  //     itp = player.erase(itp);
  // }
///////////////////////////////////////////////////END OF RESET//////////////////////////////////////////////////////////
  
  // Notify owner
  // require_recipient(asset_owner);

//////////////////////////////////////////////////////////FOR HELP//////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // // using secondary index
  // // assume paymade_table is instantiated through contract constructor
  // auto pridx = paymade_table.get_index<N(loanid)>();
  // auto itr = pridx.find( SECONDARY_KEY_WHICH_YOU_WANT_TO_FIND );
  // pridx.modify(itr, same_payer, [&](auto& p) {
  //   /* updater */
  // });
}

void nicegm::repair(eosio::name asset_owner, asset_id_type asset_id) {

  require_auth(asset_owner);

  // // check if this user is in whitelist_table
  // whitelist wluser(_self, _self.value);
  // auto wlu = wluser.find(asset_owner.value);
  // eosio::check(wlu != wluser.end(), "Can't use this function for now!!");
  // eosio::check(wlu->is_active == true, "Can't use this function for now!!");
  // // end of checking

  players player(_self, _self.value);
  gadgets gadget(_self, _self.value);

  auto iter = player.find(asset_owner.value);
  auto current_gadget = gadget.find(asset_id);

  eosio::check(current_gadget != gadget.end(), "Not found gadget");
  eosio::check(iter != player.end(), "Not found player");
  eosio::check(current_gadget->current_durability < current_gadget->durability, "Full durability");

  auto lost = current_gadget->durability - current_gadget->current_durability;
  auto coverable = 0;

  std::vector<eosio::asset> temp;
  auto sym = eosio::symbol("PLASMA", 4); // NEWT is the token symbol with precision 4

  for (auto balance = iter->balances.begin(); balance != iter->balances.end(); balance++) {
    auto current_amount = balance->amount;
    if (balance->symbol.code() == sym.code()) {
      if (balance->amount >= lost * 1000) {
        current_amount = balance->amount - lost * 1000;
        coverable = lost;
      } else {
        eosio::check(false, "Not enough plasma!");
      }
    }
    temp.push_back(eosio::asset{current_amount, balance->symbol});
  }
  player.modify(iter, _self, [&](auto &p){
      p.balances = temp;
  });

  gadget.modify(current_gadget, _self, [&](auto &g){
    g.current_durability += coverable;
  });

  require_recipient(asset_owner);

}

void nicegm::recover(eosio::name owner, asset_id_type energy_recovered) {

  require_auth(owner);

  // // check if this user is in whitelist_table
  // whitelist wluser(_self, _self.value);
  // auto wlu = wluser.find(owner.value);
  // eosio::check(wlu != wluser.end(), "Can't use this function for now!!");
  // eosio::check(wlu->is_active == true, "Can't use this function for now!!");
  // // end of checking

  players player(_self, _self.value);

  auto iter = player.find(owner.value);

  eosio::check(iter->energy < iter->max_energy, "Full energy");

  auto recoverable = 0;

  player.modify(iter, _self, [&](auto &p){

      std::vector<eosio::asset> temp;
      auto sym = eosio::symbol("OXYGEN", 4); // NEWT is the token symbol with precision 4

      for (auto balance = p.balances.begin(); balance != p.balances.end(); balance++) {
        if (balance->symbol.code() == sym.code()) {
          if ((iter->energy + energy_recovered) > iter->max_energy) {
            energy_recovered = iter->max_energy - iter->energy;
          }
          if (balance->amount >= energy_recovered * 1000) {
            balance->amount = balance->amount - energy_recovered * 1000;
            recoverable = energy_recovered;
          } else {
            eosio::check(false, "Not enough oxygen!");
            // recoverable = balance->amount * 10;
            // balance->amount = 0.0000;
          }
        }
        temp.push_back(eosio::asset{balance->amount, balance->symbol});
      }

      p.balances = temp;
      p.energy += recoverable;
  });

  require_recipient(owner);

}

void nicegm::tassetmint(eosio::name owner, std::string memo) {

  require_auth(owner);

  // // check if this user is in whitelist_table
  // whitelist wluser(_self, _self.value);
  // auto wlu = wluser.find(owner.value);
  // eosio::check(wlu != wluser.end(), "Can't use this function for now!!");
  // eosio::check(wlu->is_active == true, "Can't use this function for now!!");
  // // end of checking

  // Notify owner
  require_recipient(owner);

  configtools item(_self, _self.value);
  players player(_self, _self.value);

  auto current_item = item.find(string_to_uint64_t(memo));
  auto iter = player.find(owner.value);
  eosio::check(current_item != item.end(), "Not found configtool");
  eosio::check(iter != player.end(), "Not found player");

  auto user_asteroid = 0;
  auto user_plasma = 0;
  auto req_asteroid = 0;
  auto req_plasma = 0;
  auto sym_asteroid = eosio::symbol("ASTEROI", 4);
  auto sym_plasma = eosio::symbol("PLASMA", 4);

  std::vector<eosio::asset> temp;

  for (auto balance = iter->balances.begin(); balance != iter->balances.end(); balance++) {
    if (balance->symbol.code() == sym_asteroid.code()) {
      user_asteroid = balance->amount;
    } else if (balance->symbol.code() == sym_plasma.code()) {
      user_plasma = balance->amount;
    } else {
      temp.push_back(eosio::asset{balance->amount, balance->symbol});
    }
  }

  for (auto balance = current_item->mints.begin(); balance != current_item->mints.end(); balance++) {
    if (balance->symbol.code() == sym_asteroid.code()) {
      req_asteroid = balance->amount;
      temp.push_back(eosio::asset{user_asteroid - balance->amount, balance->symbol});
      // temp.push_back({1000000000, balance->symbol});
    } else if (balance->symbol.code() == sym_plasma.code()) {
      req_plasma = balance->amount;
      temp.push_back(eosio::asset{user_plasma - balance->amount, balance->symbol});
      // temp.push_back({1000000000, balance->symbol});
    }
  }

  // eosio::check(2 >= 3, " " + to_string(user_asteroid) + " " + to_string(req_asteroid) + " " + to_string(user_plasma) + " " + to_string(req_plasma) + " " + to_string(1234.5678));
  eosio::check(user_plasma >= req_plasma, "Not enough Plasma" + to_string(user_asteroid));
  eosio::check(user_asteroid >= req_asteroid, "Not enough Asteroid");

  // modify player's resource
  player.modify(iter, _self, [&](auto &p){
      p.balances = temp;
      // p.last_mine_tx = now(); 
  });

  // minting asset using smart contracts in atomicassets
  // get_self() means softgiant123, i.e, the owner of this smart contract code.
  eosio::action(
    eosio::permission_level(get_self(), eosio::name("active")),
    eosio::name("atomicassets"),
    eosio::name("mintasset"),
    std::make_tuple(
      get_self(), // authorized_minter
      eosio::name("galaxyminerx"), // collection_name
      eosio::name("tools"), // schema_name
      current_item->template_id, // template_id
      owner, // new_asset_owner
      std::map<std::string, atomicassets::ATOMIC_ATTRIBUTE>(), // immutable_data
      std::map<std::string, atomicassets::ATOMIC_ATTRIBUTE>(), // mutable_data
      std::vector<asset>() // tokens_to_back
    )
  ).send();

}

void nicegm::withdraw(eosio::name owner, std::vector<eosio::asset> quantities, std::uint16_t fee) {

  require_auth(owner);

  // // check if this user is in whitelist_table
  // whitelist wluser(_self, _self.value);
  // auto wlu = wluser.find(owner.value);
  // eosio::check(wlu != wluser.end(), "Can't use this function for now!!");
  // eosio::check(wlu->is_active == true, "Can't use this function for now!!");
  // // end of checking

  require_recipient(owner);

  fee = 5;
  
  players player(_self, _self.value);

  auto iter = player.find(owner.value);
  eosio::check(iter != player.end(), "Not found player");

  auto sym_asteroid = eosio::symbol("ASTEROI", 4);
  auto sym_plasma = eosio::symbol("PLASMA", 4);
  auto sym_oxygen = eosio::symbol("OXYGEN", 4);
  auto sym_GMA = eosio::symbol("GMA", 4);
  auto sym_GMP = eosio::symbol("GMP", 4);
  auto sym_GMO = eosio::symbol("GMO", 4);
  auto amount_asteroid = 0.0000;
  auto amount_plasma = 0.0000;
  auto amount_oxygen = 0.0000;
  auto user_asteroid = 0.0000;
  auto user_plasma = 0.0000;
  auto user_oxygen = 0.0000;
  auto token_asteroid = 0.0000;
  auto token_plasma = 0.0000;
  auto token_oxygen = 0.0000;
  auto used_asteroid = false;
  auto used_plasma = false;
  auto used_oxygen = false;

  std::vector<eosio::asset> temp;

  for (auto balance = quantities.begin(); balance != quantities.end(); balance++) {
    if (balance->symbol.code() == sym_asteroid.code()) {
      amount_asteroid = balance->amount;
      token_asteroid = amount_asteroid * (100 - fee) / 100;
    } else if (balance->symbol.code() == sym_plasma.code()) {
      amount_plasma = balance->amount;
      token_plasma = amount_plasma * (100 - fee) / 100;
    } else if (balance->symbol.code() == sym_oxygen.code()) {
      amount_oxygen = balance->amount;
      token_oxygen = amount_oxygen * (100 - fee) / 100;
    }
  }

  for (auto balance = iter->balances.begin(); balance != iter->balances.end(); balance++) {
    if (balance->symbol.code() == sym_asteroid.code()) {
      user_asteroid = balance->amount;
      temp.push_back(eosio::asset{static_cast<int64_t>(user_asteroid - amount_asteroid), balance->symbol});
    } else if (balance->symbol.code() == sym_plasma.code()) {
      user_plasma = balance->amount;
      temp.push_back(eosio::asset{static_cast<int64_t>(user_plasma - amount_plasma), balance->symbol});
    } else if (balance->symbol.code() == sym_oxygen.code()) {
      user_oxygen = balance->amount;
      temp.push_back(eosio::asset{static_cast<int64_t>(user_oxygen - amount_oxygen), balance->symbol});
    } else if (balance->symbol.code() == sym_GMA.code() && token_asteroid > 0) {
      temp.push_back(eosio::asset{static_cast<int64_t>(balance->amount - token_asteroid), balance->symbol});
      used_asteroid = true;
    } else if (balance->symbol.code() == sym_GMP.code() && token_plasma > 0) {
      temp.push_back(eosio::asset{static_cast<int64_t>(balance->amount - token_plasma), balance->symbol});
      used_plasma = true;
    } else if (balance->symbol.code() == sym_GMO.code() && token_oxygen > 0) {
      temp.push_back(eosio::asset{static_cast<int64_t>(balance->amount - token_oxygen), balance->symbol});
      used_oxygen = true;
    } else {
      temp.push_back(eosio::asset{static_cast<int64_t>(balance->amount), balance->symbol});
    }
  }

  if (token_asteroid > 0 && used_asteroid == false) {
      temp.push_back(eosio::asset{static_cast<int64_t>(token_asteroid), sym_GMA});
  }
  if (token_plasma > 0 && used_plasma == false) {
      temp.push_back(eosio::asset{static_cast<int64_t>(token_plasma), sym_GMP});
  }
  if (token_oxygen > 0 && used_oxygen == false) {
      temp.push_back(eosio::asset{static_cast<int64_t>(token_oxygen), sym_GMO});
  }

  // check if this user owns enough resources
  eosio::check(user_asteroid >= amount_asteroid && user_plasma >= amount_plasma && user_oxygen >= amount_oxygen, "The amount to be withdrawed exceeds the user's resource amount.");

  // withdraw token
  eosio::asset quantity;
  if (token_asteroid > 0) {
    quantity = asset( token_asteroid, sym_GMA );
    eosio::action(
        // permission_level{ _self, N(active) },
        eosio::permission_level(get_self(), eosio::name("active")), // from account
        eosio::name("galaxytokens"), // contract owner
        eosio::name("transfer"), // contract action
        std::make_tuple(get_self(), owner, quantity, std::string("withdraw asteroid")) // from, to, quantity, memo
    ).send();

    quantity = asset( amount_asteroid - token_asteroid, sym_GMA );
    eosio::action(
        // permission_level{ _self, N(active) },
        eosio::permission_level(get_self(), eosio::name("active")), // from account
        eosio::name("galaxytokens"), // contract owner
        eosio::name("transfer"), // contract action
        std::make_tuple(get_self(), eosio::name("gmxtokenfees"), quantity, std::string("withdraw fee asteroid")) // from, to, quantity, memo
    ).send();
  }
  if (token_plasma > 0) {
    quantity = asset( token_plasma, sym_GMP ); // equals to 1 EOS
    eosio::action(
        // permission_level{ _self, N(active) },
        eosio::permission_level(get_self(), eosio::name("active")), // from account
        eosio::name("galaxytokens"), // contract owner
        eosio::name("transfer"), // contract action
        std::make_tuple(get_self(), owner, quantity, std::string("withdraw plasma")) // from, to, quantity, memo
    ).send();

    quantity = asset( amount_plasma - token_plasma, sym_GMP ); // equals to 1 EOS
    eosio::action(
        // permission_level{ _self, N(active) },
        eosio::permission_level(get_self(), eosio::name("active")), // from account
        eosio::name("galaxytokens"), // contract owner
        eosio::name("transfer"), // contract action
        std::make_tuple(get_self(), eosio::name("gmxtokenfees"), quantity, std::string("withdraw plasma")) // from, to, quantity, memo
    ).send();
  }
  if (token_oxygen > 0) {
    quantity = asset( token_oxygen, sym_GMO ); // equals to 1 EOS
    eosio::action(
        // permission_level{ _self, N(active) },
        eosio::permission_level(get_self(), eosio::name("active")), // from account
        eosio::name("galaxytokens"), // contract owner
        eosio::name("transfer"), // contract action
        std::make_tuple(get_self(), owner, quantity, std::string("withdraw oxygen")) // from, to, quantity, memo
    ).send();

    quantity = asset( amount_oxygen - token_oxygen, sym_GMO ); // equals to 1 EOS
    eosio::action(
        // permission_level{ _self, N(active) },
        eosio::permission_level(get_self(), eosio::name("active")), // from account
        eosio::name("galaxytokens"), // contract owner
        eosio::name("transfer"), // contract action
        std::make_tuple(get_self(), eosio::name("gmxtokenfees"), quantity, std::string("withdraw oxygen")) // from, to, quantity, memo
    ).send();
  }

  // modify player's resource
  player.modify(iter, _self, [&](auto &p){
      p.balances = temp;
      // p.last_mine_tx = now(); 
  });
}

void nicegm::on_transfers(eosio::name from, eosio::name to, std::vector<eosio::asset> quantities, std::string memo) {

  if (memo == "deposit") {
    
    require_auth(from);

    // // check if this user is in whitelist_table
    // whitelist wluser(_self, _self.value);
    // auto wlu = wluser.find(from.value);
    // eosio::check(wlu != wluser.end(), "Can't use this function for now!!");
    // eosio::check(wlu->is_active == true, "Can't use this function for now!!");
    // // end of checking

    require_recipient(from);
    
    players player(_self, _self.value);

    auto iter = player.find(from.value);
    eosio::check(iter != player.end(), "Not found player");

    auto sym_asteroid = eosio::symbol("ASTEROI", 4);
    auto sym_plasma = eosio::symbol("PLASMA", 4);
    auto sym_oxygen = eosio::symbol("OXYGEN", 4);
    auto sym_GMA = eosio::symbol("GMA", 4);
    auto sym_GMP = eosio::symbol("GMP", 4);
    auto sym_GMO = eosio::symbol("GMO", 4);
    auto token_asteroid = 0.0000;
    auto token_plasma = 0.0000;
    auto token_oxygen = 0.0000;
    auto user_asteroid = 0.0000;
    auto user_plasma = 0.0000;
    auto user_oxygen = 0.0000;
    auto used_asteroid = false;
    auto used_plasma = false;
    auto used_oxygen = false;

    std::vector<eosio::asset> temp;

    for (auto balance = quantities.begin(); balance != quantities.end(); balance++) {
      if (balance->symbol.code() == sym_GMA.code()) {
        token_asteroid = balance->amount;
      } else if (balance->symbol.code() == sym_GMP.code()) {
        token_plasma = balance->amount;
      } else if (balance->symbol.code() == sym_GMO.code()) {
        token_oxygen = balance->amount;
      }
    }

    for (auto balance = iter->balances.begin(); balance != iter->balances.end(); balance++) {
      if (balance->symbol.code() == sym_asteroid.code() && token_asteroid > 0) {
        user_asteroid = balance->amount;
        temp.push_back(eosio::asset{static_cast<int64_t>(user_asteroid + token_asteroid), balance->symbol});
        used_asteroid = true;
      } else if (balance->symbol.code() == sym_plasma.code() && token_plasma > 0) {
        user_plasma = balance->amount;
        temp.push_back(eosio::asset{static_cast<int64_t>(user_plasma + token_plasma), balance->symbol});
        used_plasma = true;
      } else if (balance->symbol.code() == sym_oxygen.code() && token_oxygen > 0) {
        user_oxygen = balance->amount;
        temp.push_back(eosio::asset{static_cast<int64_t>(user_oxygen + token_oxygen), balance->symbol});
        used_oxygen = true;
      } 
      else if (balance->symbol.code() == sym_GMA.code() && token_asteroid > 0) {
        temp.push_back(eosio::asset{static_cast<int64_t>(balance->amount - token_asteroid), balance->symbol});
      } else if (balance->symbol.code() == sym_GMP.code() && token_plasma > 0) {
        temp.push_back(eosio::asset{static_cast<int64_t>(balance->amount - token_plasma), balance->symbol});
      } else if (balance->symbol.code() == sym_GMO.code() && token_oxygen > 0) {
        temp.push_back(eosio::asset{static_cast<int64_t>(balance->amount - token_oxygen), balance->symbol});
      } 
      else {
        temp.push_back(eosio::asset{balance->amount, balance->symbol});
      }
    }

    if (token_asteroid > 0 && used_asteroid == false) {
        temp.push_back(eosio::asset{static_cast<int64_t>(token_asteroid), sym_asteroid});
    }
    if (token_plasma > 0 && used_plasma == false) {
        temp.push_back(eosio::asset{static_cast<int64_t>(token_plasma), sym_plasma});
    }
    if (token_oxygen > 0 && used_oxygen == false) {
        temp.push_back(eosio::asset{static_cast<int64_t>(token_oxygen), sym_oxygen});
    }  

    // check if this user owns enough resources

    // withdraw token
    // eosio::asset quantity;
    // if (token_asteroid > 0) {
    //   quantity = asset( token_asteroid, sym_GMA );
    //   eosio::action(
    //       eosio::permission_level(get_self(), eosio::name("active")), // from account
    //       eosio::name("galaxytokens"), // contract owner
    //       eosio::name("transfer"), // contract action
    //       std::make_tuple(from, to, quantity, std::string("deposit GMA")) // from, to, quantity, memo
    //   ).send();
    // }
    // if (token_plasma > 0) {
    //   quantity = asset( token_plasma, sym_GMP );
    //   eosio::action(
    //       eosio::permission_level(get_self(), eosio::name("active")), // from account
    //       eosio::name("galaxytokens"), // contract owner
    //       eosio::name("transfer"), // contract action
    //       std::make_tuple(from, to, quantity, std::string("deposit GMP")) // from, to, quantity, memo
    //   ).send();
    // }
    // if (token_oxygen > 0) {
    //   quantity = asset( token_oxygen, sym_GMO );
    //   eosio::action(
    //       eosio::permission_level(get_self(), eosio::name("active")), // from account
    //       eosio::name("galaxytokens"), // contract owner
    //       eosio::name("transfer"), // contract action
    //       std::make_tuple(from, to, quantity, std::string("deposit GMO")) // from, to, quantity, memo
    //   ).send();
    // }

    // modify player's resource
    player.modify(iter, _self, [&](auto &p){
        p.balances = temp;
        // p.last_mine_tx = now(); 
    });
  }

}

void nicegm::testclaim(eosio::name asset_owner)
{
  require_auth(get_self());  // should be updated for releasing.
  // require_auth(asset_owner);

  // players player(_self, _self.value);
  gadgets gadget(_self, _self.value);
  // configtools configtool(_self, _self.value);

  // delete all data in gadgets table
  auto it = gadget.begin();
  while (it != gadget.end()) {
      it = gadget.erase(it);
  }

  // auto ct = configtool.find(string_to_uint64_t("Qmc5wLioPQwhNh7GcP35gRs1upoLHeZNBur25hGSAUnvFh"));
}

void nicegm::testenergy(eosio::name account)
{
  require_auth(get_self());  // should be updated for releasing.
  // require_auth(account);

  players player(_self, _self.value);
  auto iter = player.find(account.value);

  eosio::check(iter != player.end(), "Not found player");

  player.modify(iter, _self, [&](auto &p){
      p.energy = p.max_energy;
  });

  require_recipient(account);
}

// void nicegm::testtemp()
// {
// }

void nicegm::fixdrb()
{
  require_auth(get_self());

  gadgets gadget(_self, _self.value);

  // delete all data in a table
  auto it = gadget.begin();
  while (it != gadget.end()) {
    if (it->current_durability > it->durability) {
      // return NFT to this player from galaxyminers account back :(
      std::vector<asset_id_type> arr_item;
      arr_item.push_back(it->asset_id);

      // transfer NFT uisng action
      eosio::action(eosio::permission_level{get_self(), eosio::name{"active"}}, // Permission
                    eosio::name{"atomicassets"},                                                 // Account
                    eosio::name{"transfer"},                                      // Action
                    std::make_tuple(get_self(), it->owner, arr_item, std::string("unstake_admin"))
        ).send();
      it = gadget.erase(it);
    } else {
      it++;
    }
  }

}

void nicegm::addconfmkt(std::string schema_name, template_id_type template_id, std::string name, std::string img, std::vector<eosio::asset> cost) {

  require_auth(get_self());  

  configmarket con(_self, _self.value);

  con.emplace(_self, [&](auto &c)
                  {
                    c.schema_name = schema_name;
                    c.template_id = template_id;
                    c.name = name;
                    c.img = img;
                    c.cost = cost;
                  }
  );
}

void nicegm::delconfmkt(template_id_type template_id) {

  require_auth(get_self());

  // do something here
}

// void nicegm::setbldconf(template_id_type template_id, std::string name, std::string img, std::uint64_t charged_time, std::uint8_t required_claims, energy_type energy_consumed, std::vector<eosio::asset> craft_cost, std::uint8_t num_slots) {
//   bldconf item(_self, _self.value);

//   item.emplace(_self, [&](auto &i)
//                       {
//                         i.template_id = template_id;
//                         i.name = name;
//                         i.img = img;
//                         i.charged_time = charged_time;
//                         i.required_claims = required_claims;
//                         i.energy_consumed = energy_consumed;
//                         i.craft_cost = craft_cost;
//                         i.num_slots = num_slots;
//                       }
//               );
// }

// void nicegm::rmbldconf(template_id_type template_id) {
//   // do something here to remove items
// }

// void nicegm::setanmconf(template_id_type template_id, std::string name, std::string img, std::uint64_t charge_time, std::uint8_t daily_claim_limit, std::uint8_t required_claims, energy_type energy_consumed, template_id_type consumed_card, std::uint8_t consumed_quantity, template_id_type evolved_card, template_id_type reward_card, template_id_type required_building, template_id_type breeding_partner, std::uint8_t gender) {
//   anmconf con(_self, _self.value);

//   con.emplace(_self, [&](auto &c)
//                   {
//                     c.template_id = template_id;
//                     c.name = name;
//                     c.img = img;
//                     c.charge_time = charge_time;
//                     c.daily_claim_limit = daily_claim_limit;
//                     c.required_claims = required_claims;
//                     c.energy_consumed = energy_consumed;
//                     c.consumed_card = consumed_card;
//                     c.consumed_quantity = consumed_quantity;
//                     c.evolved_card = evolved_card;
//                     c.reward_card = reward_card;
//                     c.required_building = required_building;
//                     c.breeding_partner = breeding_partner;
//                     c.gender = gender;
//                   }
//   );
// }

// void nicegm::rmanmconf(template_id_type template_id) {
//   // do something here
// }

// void nicegm::setbreedconf(template_id_type template_id, std::string name, std::string img, template_id_type consumed_card, std::uint8_t consumed_quantity, std::uint64_t charged_time, std::uint8_t daily_claim_limit, std::uint8_t required_claims, template_id_type partner_card, template_id_type required_building, template_id_type reward_card) {
//   breedconf con(_self, _self.value);

//   con.emplace(_self, [&](auto &c)
//                   {
//                     c.template_id = template_id;
//                     c.name = name;
//                     c.img = img;
//                     c.consumed_card = consumed_card;
//                     c.consumed_quantity = consumed_quantity;
//                     c.charged_time = charged_time;
//                     c.daily_claim_limit = daily_claim_limit;
//                     c.required_claims = required_claims;
//                     c.partner_card = partner_card;
//                     c.required_building = required_building;
//                     c.reward_card = reward_card;
//                   }
//   );
// }

// void nicegm::rmbreedconf(template_id_type template_id) {
//   // do something here
// }

// void nicegm::setcropconf(template_id_type template_id, std::string name, std::string img, std::uint64_t charge_time, std::uint8_t required_claims, energy_type energy_consumed, template_id_type reward_card, template_id_type required_building, std::uint8_t miss_claim_limit) {
//   cropconf con(_self, _self.value);

//   con.emplace(_self, [&](auto &c)
//                   {
//                     c.template_id = template_id;
//                     c.name = name;
//                     c.img = img;
//                     c.charge_time = charge_time;
//                     c.required_claims = required_claims;
//                     c.energy_consumed = energy_consumed;
//                     c.reward_card = reward_card;
//                     c.required_building = required_building;
//                     c.miss_claim_limit = miss_claim_limit;
//                   }
//   );
// }

// void nicegm::rmcropconf(template_id_type template_id) {
//   // do something here
// }






// EOSIO_DISPATCH(nicegm,
//                (addplayer)(addconfitem)(delconfitem)(addsetting)(delsetting)(addconfbadge)(delconfbadge)(addbcraft)(tassetmint)(withdraw)(transfers)(addgadget)(detachgadget)(addconftool)(claim)(repair)(recover)(logopenpack)(addconfmkt)(delconfmkt)(managewl)(testclaim)(testenergy) // admin management
// );
