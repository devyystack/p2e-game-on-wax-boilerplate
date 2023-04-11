// #include <eosio/eosio.hpp>
// using namespace eosio;

// CONTRACT galaxyminers : public contract {
//    public:
//       using contract::contract;

//       [[eosio::action]] void hi( name nm );

//       using hi_action = action_wrapper<"hi"_n, &galaxyminers::hi>;
// };


#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/singleton.hpp>
#include <eosio/permission.hpp>

#define TOSTR_(T) #T
#define TOSTR(T) TOSTR_(T)

// using namespace eosio;
using namespace std;

typedef uint64_t asset_id_type;
typedef uint16_t durability_type;
typedef uint16_t energy_type;
typedef uint8_t rate_type; // uint8
typedef uint32_t resource_type;
typedef uint32_t template_id_type;

class [[eosio::contract("galaxyminers")]] nicegm : public eosio::contract
{
public:
  using contract::contract;

static constexpr uint64_t char_to_symbol( char c ) {
  if( c >= 'a' && c <= 'z' )
      return (c - 'a') + 6;
  if( c >= '1' && c <= '5' )
      return (c - '1') + 1;
  return 0;
}

static constexpr uint64_t string_to_uint64_t( std::string_view str ) {
  uint64_t n = 0;
  int i = 0;
  for ( ; str[i] && i < 12; ++i) {
      // NOTE: char_to_symbol() returns char type, and without this explicit
      // expansion to uint64 type, the compilation fails at the point of usage
      // of string_to_name(), where the usage requires constant (compile time) expression.
      n |= (char_to_symbol(str[i]) & 0x1f) << (64 - 5 * (i + 1));
  }

  // The for-loop encoded up to 60 high bits into uint64 'name' variable,
  // if (strlen(str) > 12) then encode str[12] into the low (remaining)
  // 4 bits of 'name'
  if (i == 12)
      n |= char_to_symbol(str[12]) & 0x0F;
  return n;
}
///////////////////////////////// TABLE //////////////////////////
//////////////////////////////////////////////////////////////////
  TABLE players_table {
     eosio::name account;
     energy_type energy;
     energy_type max_energy;
     eosio::checksum256 last_mine_tx;
     std::vector<eosio::asset> balances;
     // keys and indexes
     uint64_t primary_key() const { return account.value; }

     EOSLIB_SERIALIZE(players_table, (account)(energy)(max_energy)(last_mine_tx)(balances));
  };

  TABLE friends_table {
    eosio::name account;
    uint8_t tier;
    bool is_active;
    std::vector<eosio::asset> totals;

    uint64_t primary_key() const { return account.value; }

    EOSLIB_SERIALIZE(friends_table, (account)(tier)(is_active)(totals));
  };

  TABLE whitelist_table {
    eosio::name account;
    bool is_active;

    uint64_t primary_key() const { return account.value; }

    EOSLIB_SERIALIZE(whitelist_table, (account)(is_active));
  };

  TABLE check
  {
    std::uint64_t id;
    std::uint64_t claim_id;
    eosio::name validator;
    std::uint8_t is_verified; // Answer the verificator gave

    std::uint64_t primary_key() const { return id; }
    std::uint64_t by_claim() const { return claim_id; }

    EOSLIB_SERIALIZE(check,
                     (id)(claim_id)(validator)(is_verified));
  };

  TABLE badges_table {
    asset_id_type asset_id;
    eosio::name owner;
    std::string type;
    template_id_type template_id;
    std::uint64_t next_availability;
    std::uint64_t unstaking_time;

    uint64_t primary_key() const { return owner.value; }

    EOSLIB_SERIALIZE(badges_table, (owner)(type)(template_id)(next_availability)(unstaking_time));
  };

  TABLE gadgets_table {
    asset_id_type asset_id;
    eosio::name owner;
    std::string type;
    template_id_type template_id;
    durability_type durability;
    durability_type current_durability;
    std::uint64_t next_availability;

    uint64_t primary_key() const { return asset_id; }
    uint64_t by_owner() const { return owner.value; }

    EOSLIB_SERIALIZE(gadgets_table, (asset_id)(owner)(type)(template_id)(durability)(current_durability)(next_availability));
  };

  TABLE configitem_table {
    std::string schema_name;
    template_id_type template_id;
    std::string name;
    std::string img;
    bool can_burn;

    uint64_t primary_key() const { return template_id;}

    EOSLIB_SERIALIZE(configitem_table, (schema_name)(template_id)(name)(img)(can_burn));
  };

  TABLE setting_table {
    energy_type init_energy;
    energy_type init_max_energy;
    uint32_t reward_noise_min;
    uint32_t reward_noise_max;
    std::uint8_t min_fee;
    std::uint8_t max_fee;
    std::uint64_t last_fee_updated;
    std::uint8_t fee;

    uint64_t primary_key() const { return reward_noise_max; }

    EOSLIB_SERIALIZE(setting_table, (init_energy)(init_max_energy)(reward_noise_min)(reward_noise_max)(min_fee)(max_fee)(last_fee_updated)(fee));
  };

  TABLE configbadge_table {
    std::string name;
    std::uint32_t template_id;
    std::string type;
    std::string img;
    std::string badge_img;
    std::uint8_t saved_claims;
    std::uint8_t additional_slots;
    std::uint16_t additional_energy;
    std::uint8_t rewards_rate;
    std::uint8_t lucky;
    eosio::asset plasmas_mint;
    std::uint16_t coins_mint;
    std::uint64_t unstaking_time;
    std::uint64_t charged_time;

    uint64_t primary_key() const { return unstaking_time; }

    EOSLIB_SERIALIZE(configbadge_table, (name)(template_id)(type)(img)(badge_img)(saved_claims)(additional_slots)(additional_energy)(rewards_rate)(lucky)(plasmas_mint)(coins_mint)(unstaking_time)(charged_time));
  };

  TABLE badgecraft_table {
    std::uint32_t id;
    std::string name;
    std::string img;
    std::uint8_t saved_claims;
    std::uint8_t additional_slots;
    std::uint16_t additional_energy;
    std::uint8_t rewards_rate;
    std::uint8_t lucky;
    eosio::asset plasmas_mint;
    std::uint16_t coins_mint;
    std::uint64_t unstaking_time;
    std::uint64_t charged_time;

    uint64_t primary_key() const { return unstaking_time; }

    EOSLIB_SERIALIZE(badgecraft_table, (id)(name)(img)(saved_claims)(additional_slots)(additional_energy)(rewards_rate)(lucky)(plasmas_mint)(coins_mint)(unstaking_time)(charged_time));
  };

  TABLE tempassets_table {
    asset_id_type asset_id;
    eosio::name asset_owner;

    uint64_t primary_key() const { return asset_owner.value; }

    EOSLIB_SERIALIZE(tempassets_table, (asset_id)(asset_owner));
  };

  TABLE account2fa_table {
    eosio::name account;
    eosio::public_key pubkey;
    std::uint64_t features;
    std::uint64_t unlock_duration;

    uint64_t primary_key() const { return account.value; }

    EOSLIB_SERIALIZE(account2fa_table, (account)(pubkey)(features)(unlock_duration));
  };

  // TABLE bldconf_table {
  //   template_id_type template_id;
  //   std::string name;
  //   std::string img;
  //   std::uint64_t charged_time;
  //   std::uint8_t required_claims;
  //   energy_type energy_consumed;
  //   std::vector<eosio::asset> craft_cost;
  //   std::uint8_t num_slots;

  //   uint64_t primary_key() const { return charged_time; }

  //   EOSLIB_SERIALIZE(bldconf_table, (template_id)(name)(img)(charged_time)(required_claims)(energy_consumed)(craft_cost)(num_slots));
  // };

  // TABLE buildings_table {
  //   asset_id_type asset_id;
  //   eosio::name owner;
  //   std::string name;
  //   template_id_type template_id;
  //   bool is_ready;
  //   std::uint8_t times_claimed;
  //   std::uint64_t next_availability;
  //   std::uint8_t slots_usd;

  //   uint64_t primary_key() const { return owner.value; }

  //   EOSLIB_SERIALIZE(buildings_table, (asset_id)(owner)(name)(template_id)(is_ready)(times_claimed)(next_availability)(slots_usd));
  // };

  TABLE configtools_table {
    std::string template_name;
    std::string img;
    eosio::name schema_name;
    std::string type;
    std::string rarity;
    std::uint8_t level;
    template_id_type template_id;
    energy_type energy_consumed;
    durability_type durability_consumed;
    std::vector<eosio::asset> mints;
    std::vector<eosio::asset> rewards;
    std::uint32_t charged_time;

    uint64_t primary_key() const { return string_to_uint64_t(img); }

    EOSLIB_SERIALIZE(configtools_table, (template_name)(img)(schema_name)(type)(rarity)(level)(template_id)(energy_consumed)(durability_consumed)(mints)(rewards)(charged_time));
  };

  // TABLE anmconf_table {
  //   template_id_type template_id;
  //   std::string name;
  //   std::string img;
  //   std::uint64_t charge_time;
  //   std::uint8_t daily_claim_limit;
  //   std::uint8_t required_claims;
  //   energy_type energy_consumed;
  //   template_id_type consumed_card;
  //   std::uint8_t consumed_quantity;
  //   template_id_type evolved_card;
  //   template_id_type reward_card;
  //   template_id_type required_building;
  //   template_id_type breeding_partner;
  //   std::uint8_t gender;

  //   uint64_t primary_key() const { return charge_time; }

  //   EOSLIB_SERIALIZE(anmconf_table, (template_id)(name)(img)(charge_time)(daily_claim_limit)(required_claims)(energy_consumed)(consumed_card)(consumed_quantity)(evolved_card)(reward_card)(required_building)(breeding_partner)(gender));
  // };

  // TABLE breedconf_table {
  //   template_id_type template_id;
  //   std::string name;
  //   std::string img;
  //   template_id_type consumed_card;
  //   std::uint8_t consumed_quantity;
  //   std::uint64_t charged_time;
  //   std::uint8_t daily_claim_limit;
  //   std::uint8_t required_claims;
  //   template_id_type partner_card;
  //   template_id_type required_building;
  //   template_id_type reward_card;

  //   uint64_t primary_key() const { return charged_time;}

  //   EOSLIB_SERIALIZE(breedconf_table, (template_id)(name)(img)(consumed_card)(consumed_quantity)(charged_time)(daily_claim_limit)(required_claims)(partner_card)(required_building)(reward_card));
  // };

  TABLE configmarket_table {
    std::string schema_name;
    template_id_type template_id;
    std::string name;
    std::string img;
    std::vector<eosio::asset> cost;

    uint64_t primary_key() const { return template_id; }

    EOSLIB_SERIALIZE(configmarket_table, (schema_name)(template_id)(name)(img)(cost));
  };

  // TABLE cropconf_table {
  //   template_id_type template_id;
  //   std::string name;
  //   std::string img;
  //   std::uint64_t charge_time;
  //   std::uint8_t required_claims;
  //   energy_type energy_consumed;
  //   template_id_type reward_card;
  //   template_id_type required_building;
  //   std::uint8_t miss_claim_limit;

  //   uint64_t primary_key() const { return charge_time; }

  //   EOSLIB_SERIALIZE(cropconf_table, (template_id)(name)(img)(charge_time)(required_claims)(energy_consumed)(reward_card)(required_building)(miss_claim_limit));
  // };





///////////////////////////////// ACTIONS ////////////////////////
//////////////////////////////////////////////////////////////////
  /// @abi action
  /// register a new user
  [[eosio::action]] void addplayer(eosio::name owner, eosio::name referral_partner);

  // set item configuration
  [[eosio::action]] void addconfitem(std::string schema_name, template_id_type template_id, std::string name, std::string img, bool can_burn);
  // remove item configuration
  [[eosio::action]] void delconfitem(template_id_type template_id);

  // remove setting contents
  [[eosio::action]] void delsetting();
  // set setting contents
  [[eosio::action]] void addsetting(energy_type init_energy, energy_type init_max_energy, uint32_t reward_noise_min, uint32_t reward_noise_max, std::uint8_t min_fee, std::uint8_t max_fee, std::uint8_t fee);

  // set mbsconf
  [[eosio::action]] void addconfbadge(std::string name, std::uint32_t template_id, std::string type, std::string img, std::string badge_img, std::uint8_t saved_claims, std::uint8_t additional_slots, std::uint16_t additional_energy, std::uint8_t rewards_rate, std::uint8_t lucky, eosio::asset plasmas_mint, std::uint16_t coins_mint, std::uint64_t unstaking_time, std::uint64_t charged_time);
  // remove mbsconf
  [[eosio::action]] void delconfbadge(std::uint32_t template_id);

   // set badgecraft
  [[eosio::action]] void addbcraft(std:: uint32_t id, std::string name, std::string img, std::uint8_t saved_claims, std::uint8_t additional_slots, std::uint16_t additional_energy, std::uint8_t rewards_rate, std::uint8_t lucky, eosio::asset plasmas_mint, std::uint16_t coins_mint, std::uint64_t unstaking_time, std::uint64_t charged_time);

  // min tempassets
  [[eosio::action]] void tassetmint(eosio::name owner, std::string memo);

  // set toolconfig
  [[eosio::action]] void addconftool(std::string template_name, std::string img,
eosio::name schema_name, eosio::name owner, std::string type, std::string rarity, std::uint8_t level, template_id_type template_id, energy_type energy_consumed, durability_type durability_consumed, std::vector<eosio::asset> mints, std::vector<eosio::asset> rewards, std::uint32_t charged_time);

  // add a new gadget while wearing process
  [[eosio::action]] void addgadget(asset_id_type asset_id, eosio::name owner, std::string type, template_id_type template_id, durability_type durability, durability_type current_durability, std::uint64_t next_availability);

  // remove gadget
  [[eosio::action]] void detachgadget(asset_id_type asset_id, eosio::name owner);

  // mining using a tool
  [[eosio::action]] void claim(eosio::name asset_owner, asset_id_type asset_id, std::string img);

  // reparing a tool using plasma
  [[eosio::action]] void repair(eosio::name asset_owner, asset_id_type asset_id);

  // recovering energy using oxygen, 1 oxygen = 10 energy
  [[eosio::action]] void recover(eosio::name owner, asset_id_type energy_recovered);

  // withdraw
  [[eosio::action]] void withdraw(eosio::name owner, std::vector<eosio::asset> quantities, std::uint16_t fee);

  // deposit
  [[eosio::on_notify("galaxytokens::transfers")]] void on_transfers(eosio::name from, eosio::name to, std::vector<eosio::asset> quantities, std::string memo);

  // set configmarket
  [[eosio::action]] void addconfmkt(std::string schema_name, template_id_type template_id, std::string name, std::string img, std::vector<eosio::asset> cost);
  // remove configmarket
  [[eosio::action]] void delconfmkt(template_id_type template_id);

  // burning
  [[eosio::on_notify("atomicassets::transfer")]] void on_transfer(eosio::name from, eosio::name to, std::vector<uint64_t> asset_ids, std::string memo);

  // manage whitelist
  [[eosio::action]] void managewl(eosio::name owner, bool is_active);


  // test functions
  [[eosio::action]] void testclaim(eosio::name asset_owner);
  [[eosio::action]] void testenergy(eosio::name owner); // filling energy to max
  // [[eosio::action]] void testtemp(); // for dummy
  [[eosio::action]] void fixdrb(); // to fix wrong durability from bloks.io using owner account

  // // set bldconf
  // [[eosio::action]] void setbldconf(template_id_type template_id, std::string name, std::string img, std::uint64_t charged_time, std::uint8_t required_claims, energy_type energy_consumed, std::vector<eosio::asset> craft_cost, std::uint8_t num_slots);
  // // remove bldconf
  // [[eosio::action]] void rmbldconf(template_id_type template_id);

  // // set anmconf
  // [[eosio::action]] void setanmconf(template_id_type template_id, std::string name, std::string img, std::uint64_t charge_time, std::uint8_t daily_claim_limit, std::uint8_t required_claims, energy_type energy_consumed, template_id_type consumed_card, std::uint8_t consumed_quantity, template_id_type evolved_card, template_id_type reward_card, template_id_type required_building, template_id_type breeding_partner, std::uint8_t gender);
  // // remove anmconf
  // [[eosio::action]] void rmanmconf(template_id_type template_id);

  // // set breedconf
  // [[eosio::action]] void setbreedconf(template_id_type template_id, std::string name, std::string img, template_id_type consumed_card, std::uint8_t consumed_quantity, std::uint64_t charged_time, std::uint8_t daily_claim_limit, std::uint8_t required_claims, template_id_type partner_card, template_id_type required_building, template_id_type reward_card);
  // // remove breedconf
  // [[eosio::action]] void rmbreedconf(template_id_type template_id);

  // // set cropconf
  // [[eosio::action]] void setcropconf(template_id_type template_id, std::string name, std::string img, std::uint64_t charge_time, std::uint8_t required_claims, energy_type energy_consumed, template_id_type reward_card, template_id_type required_building, std::uint8_t miss_claim_limit);
  // // remove cropconf
  // [[eosio::action]] void rmcropconf(template_id_type template_id);




  // Get available key
  uint64_t get_available_id(std::string table);

///////////////////////////////// MULTI_INDEX ////////////////////
//////////////////////////////////////////////////////////////////
  typedef eosio::multi_index<eosio::name{"players"}, nicegm::players_table> players;
  typedef eosio::multi_index<eosio::name{"friends"}, nicegm::friends_table> friends;
  typedef eosio::multi_index<eosio::name{"whitelist"}, nicegm::whitelist_table> whitelist;
  typedef eosio::multi_index<eosio::name{"badges"}, nicegm::badges_table> badges;
  
  typedef eosio::multi_index<eosio::name{"gadgets"}, nicegm::gadgets_table, eosio::indexed_by<eosio::name{"byowner"}, eosio::const_mem_fun<nicegm::gadgets_table, uint64_t, &nicegm::gadgets_table::by_owner>>> gadgets;

  typedef eosio::multi_index<eosio::name{"configitem"}, nicegm::configitem_table> configitem;
  typedef eosio::multi_index<eosio::name{"setting"}, nicegm::setting_table> setting;
  typedef eosio::multi_index<eosio::name{"configbadge"}, nicegm::configbadge_table> configbadge;
  typedef eosio::multi_index<eosio::name{"badgecraft"}, nicegm::badgecraft_table> badgecraft;
  typedef eosio::multi_index<eosio::name{"tempassets"}, nicegm::tempassets_table> tempassets;
  typedef eosio::multi_index<eosio::name{"account2fa"}, nicegm::account2fa_table> account2fa;
  typedef eosio::multi_index<eosio::name{"configtools"}, nicegm::configtools_table> configtools;
  typedef eosio::multi_index<eosio::name{"configmarket"}, nicegm::configmarket_table> configmarket;


  typedef eosio::multi_index<eosio::name{"check"},
                             nicegm::check,
                             eosio::indexed_by<eosio::name{"byclaim"},
                                               eosio::const_mem_fun<nicegm::check, uint64_t, &nicegm::check::by_claim>>>
      checks;
  // typedef eosio::multi_index<eosio::name{"bldconf"}, nicegm::bldconf_table> bldconf;
  // typedef eosio::multi_index<eosio::name{"buildings"}, nicegm::buildings_table> buildings;
  // typedef eosio::multi_index<eosio::name{"anmconf"}, nicegm::anmconf_table> anmconf;
  // typedef eosio::multi_index<eosio::name{"breedconf"}, nicegm::breedconf_table> breedconf;
  // typedef eosio::multi_index<eosio::name{"cropconf"}, nicegm::cropconf_table> cropconf;


};
