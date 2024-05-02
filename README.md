## Zadanie

Jednoduchý 2D simulátor mobilních robotů.

V ohraničeném prostředí obdélníkového půdorysu je situován libovolný počet robotů.  Robot má tělo kruhového půdorysu a je schopen pohybu vpřed danou rychlostí, otočení o daný úhel a detekce kolizí. V prostředí se mohou vyskytovat statické překážky. Překážky jsou tvořeny libovolným počtem čtverců dané velikosti na zvolených souřadnicích. Počáteční rozmístění překážek a robotů (včetně jejich orientace a dalších parametrů) lze stanovit interaktivně v GUI, lze ho uložit do souboru v čitelné a ručně editovatelné textové podobě  a načíst. 

Podle způsobu řízení lze rozlišit 2 typy robotů: 

1. Autonomní robot se ve volném prostředí pohybuje přímočaře a vyhýbá se kolizím tak, že při detekci překážky v dané vzdálenosti (parametr robota) se otočí o daný úhel (parametr robota) daným směrem (parametr robota) a pokračuje stejným způsobem dál.

2. Dálkově ovládaný robot přechází podle pokynů operátora mezi stavy žádný pohyb, pohyb vpřed, otáčení proti směru hodinových ručiček, otáčení po směru h.r. Pokud detekuje překážku, zastaví svůj pohyb vpřed.

GUI umožňuje ovládání simulátoru a vizualizuje simulaci. Zobrazuje mapu prostředí s překážkami a roboty a obsahuje ovládací prvky pro dálkové ovládání vybraného robota. Simulaci lze spustit z výchozího stavu, pozastavit, nechat pokračovat. Simulace pracuje se zjednodušenou fyzikou, pracující s diskrétním časem, spojitým 2D prostorem a rovnoměrným přímočarým pohybem danou rychlostí a rovnoměrnou rotací danou úhlovou rychlostí (nebere se v úvahu hmotnost, setrvačnost, zrychlení apod., pouze vzdálenost, rychlost, úhlová rychlost a čas). Simulace i vizualizace probíhá ve vhodně zvolených časových krocích. Kroky by měly být dostatečně jemné (vzhledem k rychlosti pohybu), aby robot stihl detekovat překážku dříve, než dojde ke kolizi a také aby vizualizace probíhala zdánlivě plynule.

## Spustenie

./robots