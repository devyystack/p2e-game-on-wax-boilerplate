16.00 UTC 19 of march

Hi. I'm looking for a crypto game dev.
We have all graphics and game rules/math.

demo version
1: put all the icons you got so that the game does not look like farmersworld
2. remove that map that they painted over, there is also a farmersworld card in the middle. so that we have no connection with farmersworld.
3. add all the buttons we sent with, you have got a layout on it.
4. there is no interaction with blockchain
5. We must have an interaction with an nft
6. we need to be able to see our NFTs in the demo,
integrate our nfts into the demo with the possibility to make an action based on a smartcontract. the action should be visible on the testnet on https://wax-test.bloks.io/


1. Stake and unstake on all tools
2. Get tools to use both ingame tokens and generate them based on the formulas (in the doc)
3. Able to "craft"
4. Withdraws
5. Real tokens, ingame tokens -> real tokens 


(FOR DEMO)
Before friday and before we keep going with all other smartcontracts.
1) make buttons same colour and the corners are cut off fix these
2) show resource icon(big) in the background of card information
3) on craft page: make all cards have the correct rarity, rewardrate, charge time (1hour), energy consumed, durability consumed
4) craft cost symbols between (craftcost) and (craft) change to bigger, white text on numbers and correct craft cost
5) exchange page: text - PLASMA ASTEROID OXYGEN GMP GMO GMA little bit bigger text
6) energy button: change numbers to white


BUG LIST:

1. NFT Pictures slow loading (or not loading at all)
2. First login only works with "active" user, should also work with "owner"
3. After refilling energy or repairing, the resources return to your balance
4. Some times when staking, items dissapear from users game and inventory
5. When mining 1 tool, sometimes that tools timer will show on other tools
6. Someone managed to mine a tool every minute, not sure if he unstaked and staked, or reset the timer


Most issues I found was Visual bugs.
-overlaps numbers when it is not maximize. (Zoom 100%), what ever the size, the number should not overlaps on the box.
-Cannot see the unstake botton of NFT. (in second pic)
-Countdown Timer - when you go to the next NFT, the remaining time of the first mined NFT will reflect on the second one.
-When staking an Item, after the transaction of the Anchor, NFT will stay like 5 secs before it will disappear.

Missing item - When I stake my Asteroid Scanner, i could not find in the inventory. Experience this last time, I lost my 2 NFTs.

Suggestion:
When Mouse over the icons on lower right, info should show what is it. Currently no info is showing. Atleast indicate the name of the icon.
So far, all functions are good except for the delay when staking an item, crafting- haven't tried it yet and the missing item. 


1) make smartcontracts efficient lower the amount of times you have to sign transactions
2) SECURITY SUPER IMPORTANT. create a new account and try to abuse the game.
3. i have not tried crafting can you update it all for demo server so we can try
4. there is some UI needed. 
5. i want to add REQ for unstaking, (NEED 500 energy to unstake) but it does not remove 500 energy, just have to have it.
6. alcor exchange
7. when withdrawing it is at 0% at first and it takes time to update to 5%. have it always set for 5%
8. i will give you some UI for when  it says "you need to repair tools"


--USER INTERFACE BUGS and add features:
1.Center all text for ALL buttons
2.timer moving around needs to stay still
3.the purple bar should go down slowly based on how much u have, same as energy ba
4.I dont know how to explain but the box showing up "you cannot wear more than 8 tools!" this box will be changed we will give you UI for it.(also we want same font in error box)
5.change fee button font to same as others
6.bigger resource icons on "craft" (same size as top resource icons)

--GAME BUGS and add features: 
1.stake is double sign, needs to be one signed transaction
2.when going to "exchange button" it shows 0% at first. change it to static 5 %
3.change Asteroid dissolver durability to 600 

--after this
ALL focus on securing the game
--after that
focusing on expansion of the game

-- time traveler machine
and if u have the membership :
increase total energy bar
increase tool capacity
stored mining(you dont have to mine as often)

TIME MACHINE TEMPLATE ID: #397643
SHARD TEMPLATE ID: #397642
CRYSTAL TEMPLATE ID: #397641

14 template in total

Empty Scrap time machine
Scrap Asteroid TIme machine
Scrap Pasma TIme machine
Scrap PxygenTIme machine

Empty Obsidian Time machine
Obsidian Asteroid TIme machine
Obsidian pasma TIme machine
Obsidian oxygen TIme machine

Empty unidentified Time machine
 unidentified Asteroid TIme machine
 unidentified pasma TIme machine
 unidentified oxygen TIme machine

+ Crystal , shard


1. Three empty timemachines is shown in Store tab in game.
2. after crafting them, they should just be inside inventory,
3. blend into a time machine(you dont have to worry about this step)
4. Stake card
5. mine every 48 hours to get shards 

SCRAP -

ASTEROID - 397643
OXYGEN - 397680
PLASMA - 397681
EMPTY - 397682

OBSIDIAN - 

ASTEROID - 397685
OXYGEN - 397686
PLASMA - 397687
EMPTY - 397683

UNIDENTIFIED - 

ASTEROID - 397688
OXYGEN - 397689
PLASMA - 397690
EMPTY - 397684


-- Minecraft API
1. Read info on player(s)
2. Put random placed pre-designed "objects" in the game and hide/show them
3. If a player "hits or grab" a specifik object, and points/rewards back to players WAX -account
4. Connect WAX account to Mojang account


Similar functions as:
https://farmersworld.io       LoginInfo: waxwallet123 testwalletgameplay@gmail.com

password : Testtest123123 email : fwplot1@gmail.com


Linus contact info: straightgames@hotmail.com              +46732707500

https://spacecraftx.io/

/////////////////////////////////////////////////////////////////////////////
https://www.section.io/engineering-education/minecraft-plugin-development-a-hands-on-crash-course/  ==>>  NFTworry and Minecraft,  Spigot or BungeeCord API



- All under WAX, recourses;
https://developer.wax.io/quickstarts/dapps/
https://developers.eos.io/         // for blockchain transactions
https://developers.eos.io/manuals/eosio.cdt/latest/index
https://developers.eos.io/manuals/eosio.cdt/v1.7/structeosio_1_1asset   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
https://developers.eos.io/welcome/v2.0/tutorials/tic-tac-toe-game-smart-contract-Testnet
https://wax.atomichub.io/                         https://wax-test.atomichub.io/   to deploy NFTs
https://wax-test.atomichub.io/creator/collection/galaxyminerx/schema/tools   // NFTs for galaxyminers
https://guide.eoscostarica.io/docs/eos-learn/smart-contract/
https://docs.eosstudio.io/contracts
https://github.com/blockmatic/eosio-contracts-list
https://eosio-cpp.readme.io/v1.1.0/docs/using-multi-index-tables
developers.eos.io/manuals/eosio.cdt/v1.8/best-practices/debugging_a_smart_contract
developers.eos.io/manuals/eosio.cdt/v1.7/how-to-guides/authorization/how_to_restrict_access_to_an_action_by_user
developers.eos.io/manuals/eos/v2.1/cleos/command-reference/set/set-account-permission
developers.eos.io/welcome/latest/smart-contract-guides/deploy-issue-and-transfer-tokens

https://neftyblocks.com/c/galaxyminerx/packs

https://docs.alcor.exchange/developers-api/market-creation/token-logo

https://docs.alcor.exchange/developers-api/contract-tables
https://wax.bloks.io/account/alcordexmain?loadContract=true&tab=Actions&account=alcordexmain&scope=alcordexmain&limit=100&table=settings&action=setmfee

- atomicassets contract
https://github.com/pinknetworkx/atomicassets-contract/wiki

https://dapplica.io/blog/general/the-guide-to-development-of-auctions-on-wax-blockchain/
https://community.eosstudio.io/latest?sortOrder=ByBumpTime&olderThan=1562298437909
https://steemd.com/recent/eosio



https://wax.bloks.io/account/5oigm.wam            

https://wax-test.bloks.io/account/5oigm.wam     galaxyminers1
{"msg": "succeeded", "keys": {"active_key": {"public": "EOS72hyfJJoANU1sYyUwnG95hFuEPR3iBpZgxz3QPi9Bxmta66nXA", "private": "5JMyzuirH54Brj8crAduHsPkLvRK7JSP78pHT6391b8CfK7bzJ6"}, "owner_key": {"public": "EOS79RWdM1dLa39gGP2F785uLAx8yWyNVudiHeRxr55mfF57irB5L", "private": "5JZwEPdifES8XxnN41w3xRC5e2uUsQtUE3YkG9xMY3RbWrXXUhA"}}, "account": "galaxyminer1"}
”Private”

https://wax.alcor.exchange/
https://wax.alcor.exchange/new_market
https://waxsweden.org/create-testnet-account/

/////////////////////////////////////////////////NFTS
https://test.neftyblocks.com/c/galaxyminerx/drops/1187             // new cards
https://test.neftyblocks.com/c/galaxyminerx/drops/1189             // old cardss


///////////////////////////////////////////////////////////////////////////////
wallets
wax: https://wallet.wax.io/eth-bridge
anchor: https://bloks.io/
	https://greymass.com/en/anchor/download/
	private key: 5JZwEPdifES8XxnN41w3xRC5e2uUsQtUE3YkG9xMY3RbWrXXUhA  
	password: This1i~.

///////////////////////////////////////////////////////////////////////////////
To see all transactions and tokens on wax blockchain
https://wax-test.bloks.io/
https://wax.bloks.io/account/farmersworld 
https://wax-test.bloks.io/account/farmersworld 
https://wax.eosio.online/endpoints




/////////////////////////////////////////////////////////////////////////////////
https://galaxyminers.testmats.se
play.galaxyminers.io
galaxyminers.io

- galaxyminers.chrushdigital.se
putty
host: galaxyminers.chrushdigital.se      username: urbanhai           pass: 'b~8+bAP'Ps3E%aL         for demo

- demo.galaxyminers.io
putty
host: linux267.unoeuro.com                       : galaxyminers.io        : nG64EeadrFB9             for hype

- https://whitepaper.galaxyminers.io/#typesofrarity


https://www.udemy.com/course/wax-blockchain/
https://support.pink.gg/hc/en-us/articles/4405472261650-What-are-the-requirements-to-get-whitelisted-


/////////////////////////////////////////////////////////////////////////////////
This is the demo req for Atomic Hub:
a) Wallet login (Cloud-Wallet, Anchor)
b) List of game-based NFT's the user has in his wallet, as shown in the frontend
c) A minimal interaction with your own smart contracts


1. Users will use some blockchain wallet in order to log-in into the game (let’s assume it’s a WAX Cloud Wallet by default). 
2. With every new game round, the user will push some action into the blockchain via wallet, so this action can be recorded 
for logging user’s activity. 
3. When a user wins or fails a round we would also recommend to write an action with details, so it can add-up into the 
user’s profile(like number of games played, or via XP points if the user is gonna receive ones), as well as some in-game token.
4. WAX itself has in-built random service, so it can be used in order to provide better transparency in some sensitive gameplay 
moments. 
5. As for Tokenomics part we can design it next way:
- GOLD token, received for every round won. GOLD token would be non transferable (and non tradable), 
- GEM token, can be received in some rare cases or/and purchased for WAX token. This token can be used to purchase additional 
life, so users can replay rounds and provide options for some skins / cosmetics. 
- Users can play every round for free, or even pay for it. Or we can add a special ladder / leaderboard mode, where users 
compete for a shared prize pool. Following approach can be next, a weekly leaderboard where the user pays 10 WAX per trial, 
and receives points to move in the leaderboard. Leaderboard itself has a pot, which grows till distribution moment, 
once time is out a pool is distributed by certain rules to TOP competitors. Additionally, GEM token can be issued 
as a small bonus on top of every purchase via WAX in-game. 
- NFTs. In this game we might use NFTs, but not mandatory. For example we can make some drops of achievements as NFTs, 
so users can sell them, this should be designed extremely carefully, so scarcity of NFTs can be met. 
NFTs can be also designed as Cards to drop, collections to make or badges to earn, however this is a subject of more 
complex game examples and our NEST platform idea, we will describe it in following articles. 


play.farmersworld remote addr: 95.217.57.149:443

// add a permission for eosio.code to an active account to allow inline actions to run without signature
View account > wallet > keys and permission > advanced > permission #2 active > +1 softgiant123 eosio.code > add account

// transfer files from windows to vm ubuntu
https://linuxize.com/post/how-to-install-vmware-tools-in-ubuntu-18-04/

sudo apt update
sudo apt install open-vm-tools

// eosio-init
wget https://github.com/eosio/eosio.cdt/releases/download/v1.8.0/eosio.cdt_1.8.0-1-ubuntu-18.04_amd64.deb
sudo apt install ./eosio.cdt_1.8.0-1-ubuntu-18.04_amd64.deb  // install CXX compiler

sudo apt-get install build-essential

// install cleos
wget https://github.com/EOSIO/eos/releases/download/v2.0.5/eosio_2.0.5-1-ubuntu-18.04_amd64.deb
sudo apt install ./eosio_2.0.5-1-ubuntu-18.04_amd64.deb

/////////////////////////////////////////////////////////////////////////////////////////////////
eosio-init -project <projectName>
cmake .. // in build folder
make


firstwallet: PW5JaarFH5hVdp69irLnX9bZTtjpm2jWmV4WVUcHNxmDgG663u3r5
gmwallet: PW5KR3bwV4mRfnbhgtqa6kwvMWtuPaftNCKT74ajT2P7A2TAJRpv4
// 
cleos wallet open -n gmwallet &&
cleos wallet unlock -n gmwallet --password PW5KR3bwV4mRfnbhgtqa6kwvMWtuPaftNCKT74ajT2P7A2TAJRpv4

// 
cleos rm -f ~/eosio-wallet/gmwallet.wallet &&
 cleos wallet create -n gmwallet --to-console &&
 cleos wallet import -n gmwallet --private-key 5JAZTL63Jmv2xqBYndC4aNto6FHZgDVjBMuiG5FpFt9pGPERKnz &&
 cleos wallet import -n gmwallet --private-key 5Jpdg68HNMK9N4cusQYt14tfmeA6ddQ2kMRjnxHXyTihbytVtrd

// buy resources
cleos -u https://testnet.waxsweden.org system buyram softgiant123 softgiant123 "3.00000000 WAX"
cleos -u https://testnet.waxsweden.org system delegatebw softgiant123 softgiant123 "4.00000000 WAX" "5.00000000 WAX"

// deploy  in build/galaxyminers folder
cleos -u https://testnet.waxsweden.org set contract softgiant123 $(pwd) galaxyminers.wasm galaxyminers.abi

// run
cleos -u https://testnet.waxsweden.org push action eosio claim '{"asset_owner":"galaxyminer1", "asset_id": 1099524860777}' -p eosio
///////////////////////////////////////////////////////////////////////////////////////////////////

---- create eos token: Another account should be used for this. Not same one with game account!
https://developers.eos.io/manuals/eosio.contracts/latest/guides/how-to-create-issue-and-transfer-a-token

- create and unlock wallet for token.
cleos wallet create -n tokenwallet --to-console &&
cleos wallet import -n tokenwallet --private-key 5J9kEfe7mRkkANZUK5b8rnzT9WFmauawfzVvXLTMUkR49iVVZnd &&
cleos wallet import -n tokenwallet --private-key 5HucRp7CH92JoMsVB1jbjJFhmwZ2Z4wU5DnQGN47WCYyH5ccNDA

cleos wallet open -n tokenwallet &&
cleos wallet unlock -n tokenwallet --password PW5KEDvqSavvbMm5nszRfQG3PdQsuggKemrmsrxtpmZVdwUXgTv99

- move to eosio.contracts/contracts/eosio.token

- compile contract
eosio-cpp -I include -o eosio.token.wasm src/eosio.token.cpp --abigen

-deploy token
// cleos set contract eosio.token CONTRACTS_DIR/eosio.contracts/contracts/eosio.token --abi eosio.token.abi -p eosio.token@active
cleos -u https://testnet.waxsweden.org set contract galaxytokens ./ --abi eosio.token.abi -p galaxytokens@active

/////////////////////////////////////////////////////////////////////////////////////////////////////
---- alchor exchange
https://wax.alcor.exchange/
https://github.com/avral/alcor-ui
/////////////////////////////////////////////////////////////////////////////////////////////////////
test net
account:
	{"msg": "succeeded", "keys": {"active_key": {"public": "EOS7WtqJXmsEW4Aq9NBFiqK9ALj7WjnpZcF9cZ2H86numeJWRUPrc", "private": "5JAZTL63Jmv2xqBYndC4aNto6FHZgDVjBMuiG5FpFt9pGPERKnz"}, "owner_key": {"public": "EOS79DGtYyK3p7GDazs9z3CGSwLBmkNPHYJit8chofR1G2s4xhYsg", "private": "5Jpdg68HNMK9N4cusQYt14tfmeA6ddQ2kMRjnxHXyTihbytVtrd"}}, "account": "softgiant123"}
	{"msg": "succeeded", "keys": {"active_key": {"public": "EOS5fgc1BXSyZrdggPE7GmqMtUHxo2PitQus6Rnm1kf1n1gRFbQ4T", "private": "5KVPjWrd8oeCoCDFsBoqDEGWJb4e27A5BHVR8k9zbxNSLjCtEur"}, "owner_key": {"public": "EOS7xWJGCTZtQYpGyuGUggfxuWTFkVXiUcahfW9xEwaAV6hxYE1du", "private": "5KF6spvuePGiJPNFxxapatp2qHQjM2X7U25p3LDgqQga9Avetw1"}}, "account": "softgiant234"}
	{"msg": "succeeded", "keys": {"active_key": {"public": "EOS833buga33Kt9vktSV8LiYaFvsJTeib8f6BEAYnEWX2bHe3idXM", "private": "5JVz4fXEC515wPdFE4ZFkHwMzcN7zYSeLsu2YiuyRwXU5fqHSvM"}, "owner_key": {"public": "EOS5AwT9dDa8ZstmBzvMWeQJXh9T3fEd64vTeSugH3ajfd2ekjrZv", "private": "5JgE6gMmuySsdg5WCALZShCYtExYzXA5LfoMBKpimevtUjuRtZ2"}}, "account": "softgiant345"}
	{"msg": "succeeded", "keys": {"active_key": {"public": "EOS8cvMVkVrkeh72KuSiEXAqyrMcgcaiYsjW6geLXg1QU998Pc7en", "private": "5J9kEfe7mRkkANZUK5b8rnzT9WFmauawfzVvXLTMUkR49iVVZnd"}, "owner_key": {"public": "EOS7DYJPxkvG2FptwsqX7hpnKSnLbt2LLhzP3tUYtMoR7QiL2fTnf", "private": "5HucRp7CH92JoMsVB1jbjJFhmwZ2Z4wU5DnQGN47WCYyH5ccNDA"}}, "account": "galaxytokens"}
	{"msg": "succeeded", "keys": {"active_key": {"public": "EOS6H8Gn39KzYRbQ5Nhz8Z6wvX9cnZEzSGPxHJSpLzaZipedHyj2w", "private": "5JGvZXZ4bfhknpqhRbEMtja2vJQMwBmgYoTegTgyw2UMuPRhGYe"}, "owner_key": {"public": "EOS8aUSzV7wRXrXRhS5S5RtSDrmGVJG5NwbNm8Ej7kdKdRmjGYTrW", "private": "5JgVd6KAowcRHBS5nX1g2rvyNrmLd3qcKjp7NQp2f54puMknAcs"}}, "account": "galaxytokenr"}
	{"msg": "succeeded", "keys": {"active_key": {"public": "EOS6n6HRrNreWZA67wvwA6bMadyTzievB2xnL3YSbFej53AXNUsp1", "private": "5JWfCrBaW7MT4FxUpqxVv9mozNLX54Hgp4H3Zunu6LSq8tA2CYE"}, "owner_key": {"public": "EOS5AT2wr8dWq4Z3RCJAcK8dYtuPwZd4VZpVG11ZfietgBAMQSL56", "private": "5J6NNmH4bbA7RknambkTTzyKtJyFdRtBGfDAnvEeNFkUCDpW1kV"}}, "account": "bugfixing123"}
	{"msg": "succeeded", "keys": {"active_key": {"public": "EOS7xgNJXEmj9wHB6h7xiro5bYwDE1aAfL3zUWwdg5xw14pXQEFHD", "private": "5Kc83JdUUFJoTYDEmhGdxz7qEjUcCqWBN2EqAW39Emax3dttJMk"}, "owner_key": {"public": "EOS6uwUgfhw6hjJVc8Um7b7HW5JU2JEsuJtY7Xw4Y3AGSvEHmKXEL", "private": "5HpHmMFqHXYH59H7ZYgMvtmaEvNppG7h5snRccb7csRbHKkmpFm"}}, "account": "bugfixing234"}
	{"msg": "succeeded", "keys": {"active_key": {"public": "EOS56UgpmguKAiSKqPbn8zcKYf4CnipKdz1UoKjPZeYcLjS9Hqpoj", "private": "5KBCqMPczAbwS5VVcz8cPJaoGTsbu6KJfciv3j54nKcyszWU8Ph"}, "owner_key": {"public": "EOS7mXf647RX9jwGZ1h4iwtysJmXeiykL58wGBRzEjc7fX8hxr63a", "private": "5JcuTvm2FK6EYrQ4HtorXSqXaPyteGdreF1Q7ov8UynXkvTDHbA"}}, "account": "bugfixing345"}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

plasma ionizer : QmWNseSc6Tb5EoVrhD8oADVQyCvZiMvmGwMYD4PxnX5i2s
plasma collector; Qmcw4wsEWDBQHWMBFPJRQ8eWDoAGcSqLShA59tiRCU4bX1
oxygen tank: QmNpzNmSzKK2karhEvbzXK3MWZGmMq9yQNDXmvmpXB1CPy
oxygen backpack test : QmV6jQZUGr257a5hNVnkM4mjSX1ecU7M9AKkAkXAbSBh2u
oxygen jar : QmdyRsrNJYkCUoe6Lbmf9YSCpLycqtctLrypMaEYk4x9pN

dissolver : QmTvQ7K21U4v8Df22vY5JXfNR1ok5WmS38eyodkTN4orhj

Drone: Qmd8GbskfeoU8AixhWNYSVZKHPrnbSH3o4mC7XPu3HJeoa

cleaver : QmV1kCoQ8KiE5P9cKrtYfdHHFVyMCyZJBqNsfHS2B157zA

scanner : QmWYrC7sDuVS5VLH67Go6f5XgJt93XbaTpJrFheY6eDNKi


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
real version
- accounts
galaxyminers   main account
galaxytokens   tokens
gmxtokenfees   fee
galaxyminerx   collection name

- sites
femfemma.galaxyminers.io

servername: shine.oderland.com
username: ehemsid8
password: \e4N^}4d_K6^DxR,
passphrase: \e4N^}4d_K6^DxR,

- unlock wallet
cleos wallet open -n galaxyminers &&
cleos wallet unlock -n galaxyminers --password PW5K2iULGmocWa7UeQZArY6FKd6hsDD7sXztKcNSinHK511YJpoJ8

- deploy contracts
cleos -u https://api.waxsweden.org set contract galaxyminers $(pwd) galaxyminers.wasm galaxyminers.abi


---- manage token
- unlock wallet
cleos wallet open -n tokenwallet &&
cleos wallet unlock -n tokenwallet --password PW5KasQExvGGRR8XX3u7zJ8VdCHss2QRsz6HmmSZ5B6Szc2puvKXh

- move to eosio.contracts/contracts/eosio.token

- compile contract
eosio-cpp -I include -o eosio.token.wasm src/eosio.token.cpp --abigen

-deploy token
// cleos set contract eosio.token CONTRACTS_DIR/eosio.contracts/contracts/eosio.token --abi eosio.token.abi -p eosio.token@active
cleos -u https://api.waxsweden.org set contract galaxytokens ./ --abi eosio.token.abi -p galaxytokens@owner

------------ teamviewer
858 835 610
fvcwu3m4
---------- wallets

galaxytestin owner PVT_K1_wM69Q9dLaCCTzSAbZWfRZDPrg2i4uEXMpE2VV7dBYnDabmBvt  active key PVT_K1_5NjKrW4of4Ld2mL92uZ2HUfVjjARhnfHnaDwB79Xt8xHYjBoR




template for asteroid : 347966 

template for oxygen 347967

template for plasma 347968



https://www.huobi.com/en-us/topic/mining
