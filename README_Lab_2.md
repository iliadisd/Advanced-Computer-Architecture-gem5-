# Αρχιτεκτονική Προηγμένων Υπολογιστών
## Εργαστήριο 2Β Ομάδα 1 | Ηλιάδης-Αποστολίδης Δημοσθένης 8811

## Ερωτήματα


### 1.1 Κάθε benchmark από αυτά που τρέξαμε έχει ίδια configurations για το σύστημα της προσομοίωσης, πράγμα λογικό, αφού το spec_cpu2006 είναι ένα benchmark suite που βγήκε το 2006 από την SPEC και θα έχει κοινά χαρακτηριστικά αναφορικά με τα benchmark configurations.

Στα config.ini έχουμε :
<pre>
@system:
cache_line_size = 64
</pre>
<pre>
@system.cpu.icache:
size = 32768  (~32kB)   L1 Instruction Size
L1 Instruction Associativity = 2
</pre>
<pre>
@system.cpu.dcache:
size = 65536  (~64kB)   L1 Data Size
assoc = 2   L1 Data Associativity
</pre>
<pre>
@system.l2:
size = 2097152  (~2MB)
assoc = 8
</pre>

### 1.2 Οι ζητούμενες τιμές και το διάγραμμα είναι το παρακάτω :

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab2/1_2.png?raw=true)

<pre>
Παρατηρούμε, ότι τα benchmarks τα οποία έχουν μεγαλύτερα missrate στην L2 cache έχουν μεγάλο CPI. Αυτό είναι κάτι το
λογικό γιατί η L2 cache είναι πιο αργή από την L1, πράγμα που σημαίνει ότι κάθε φορά που θα έχω miss θα
αυξάνεται και ο χρόνος που θα χρειάζεται για να ολοκληρωθεί ο κάθε κύκλος.
</pre>

### 1.3 Με την παράμετρο--cpu-clock=2GHz δεν αλλάζει κάτι καθώς τα αποτελέσματα που παίρνω είναι :

<pre>
*system.clk_domain.clock = 1000
*system.cpu_clk_domain.clock = 500
</pre>

Με δοκιμή στα 1 GHZ, το system.cpu_clk_domain.clock άλλαξε σε 1000. Οπότε εικάζω ότι τα benchmarks είτε ότι μπορούν να
τρέξουν μέχρι 1 GHz ή ότι το 2ghz είναι το default. Επίσης από την  δοκιμή στο 1 GHz, το CPU βρίσκεται στο
system.cpu_clk_domain, ενώ στο system.clk_domain βρίσκονται στοιχεία του συστήματος, πράγμα λογικό, αφού το λέει και
το όνομα. Τέλος, πιστεύω ότι θα προσθέταμε 2 GHz επεξεργαστή, όσο και ο πρώτος, αν και δεν έχει νόημα να προσθέσω κάποιον
επεξεργαστή, χωρίς να τρέχω το benchmark παράλληλα.

### 2.1 Design Exploration

Σε γενικές γραμμές, κάθε ένα από τα παρακάτω χαρακτηριστικά επηρρεάζουν το CPI με διαφορετικό τρόπο.
Όσον αφορά τα simulations των benchmarks που είναι κοντά στο 1, Θεωρώ πως τα πιο κρίσιμα στοιχεία του
simulation να τα πειράξω θα είναι το associativity των caches, καθώς αυτό είναι υπεύθυνο σαν policy
για το Cache Placement,αλλά και το size της L1 cache η οποία είναι και πιο γρήγορη σε προσπέλαση.
Φυσικά εκεί που έχουμε μεγάλα missrates είτε σε L1 είτε σε L2 θα χρειαστεί να μεγαλώσουμε το cache line size,
το size του L1 icache/dcache ανάλογα και του L2 αντίστοιχα, καθώς και το associativity για να μειώσουμε τα misses.
Στο επόμενο ερώτημα θα δούμε τις διαφορές που επιτεύχθηκαν ανάλογα με τις αλλαγές που κάναμε στο κάθε simulation.

<pre>
* L1_icache_size
* L1.icache.assoc
* L1_dcache_size
* L1.dcache.assoc
* L2_cache_size
* L2.cache.assoc
* cache_line_size
</pre>

##bzip
Στο default simulation του benchmark, το CPI είναι ήδη κοντά στο 1. Aπό το stats.txt,
κάτι που θα μπορούσε να βοηθήσει στην επιπλέον μείωση του CPI είναι η αύξηση του
L1.dcache.assoc (8)και η αύξηση του L1_dcache_size (128kB).

<pre>
*bzip_default system.cpu.cpi = 1.673085
</pre>

##hmmer
Και εδώ το CPI είναι κοντά στο 1. Από το stats.txt βλέπουμε ότι μπορούμε να βελτιώσουμε τα missrates, αυξάνοντας
το cache_line_size (128), το L1_dcache_size (-->128kB) και το L1.dcache.assoc (8).

<pre>
*hmmer system.cpu.cpi = 1.404100
</pre>

##libm
Εδώ το L2 missrate είναι πολύ μεγάλο, θα αυξήσω τα L2_cache_size(512),
L2.cache.assoc(8) και το cache_line_size (128).

<pre>
*libm system.cpu.cpi = 3.495270  
</pre>

##mcf
Έχω μεγάλο l1_icache missrate, οπότε επιλέγω να αυξήσω τα L1_icache_size(128) και L1_dcache_size(64),
καθώς και τα assoc(8) τους.

<pre>
*mcf system.cpu.cpi = 1.251067
</pre>

##sjeng
Ομοίως με παραπάνω, θα αυξήσω τα L2_cache_size(512), L2.cache.assoc(8) και το cache_line_size (128).

<pre>
*sjeng system.cpu.cpi = 10.276466
</pre>

### 2.2 Μετά από διάφορες δοκιμές και με βάση τα προηγούμενα ερωτήματα κατέληξα στις παραπάνω επιλογές. Παρακάτω φαίνεται το διάγραμμα στο οποίο συγκρίνω το κάθε simulation του κάθε benchmark μεταξύ του με βάση τους CPI.

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab2/bzip.png?raw=true)

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab2/hmmer.png?raw=true)

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab2/libm.png)

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab2/mcf.png?raw=true)

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab2/sjeng.png?raw=true)

### 3. Κόστος απόδοσης και βελτιστοποίηση κόστους/απόδοσης
Σύμφωνα με τα προηγούμενα βήματα, οι παράμετροι που επηρεάζουν το κόστος απόδοσης περισσότερο είναι παρακάτω:

<pre>
* L1_icache_size
* L1.icache.assoc
* L1_dcache_size
* L1.dcache.assoc
* L2_cache_size
* L2.cache.assoc
* cache_line_size
</pre>

##L1 Cache size - L2 Cache size
Η L1 cache είναι περίπου 100 φορές γρηγορότερη από μια τυπική ram, ενώ η L2 25 φορές. Συνεπώς η L1 είναι 4 φορές
γρηγορότερη από την L2. Επίσης η L1 χωρίζεται σε instruction και data(icache, dcache). Τέλος η L1 είναι πολύ
ακριβότερη από την L2. Σύμφωνα και με την εκφώνηση,

*Cost(l1_cache_size) = 5 * Cost(l2_cache_size)

#### L1 Cache associativity -  L2 Cache associativity
Επειδή η L1 cache βρίσκεται πιο κοντά στον επεξεργαστή από ότι η L2, η πρόσβαση στην L1 είναι πιο κοστοβόρα από την
πρόσβαση στην L2. Επίσης, επειδή η L1 θα είναι μικρότερη σε μέγεθος, πρέπει να την φορτώνω μόνο για τα πολύ
σημαντικά tasks. Συνεπώς
*Cost(l1_cache_assoc) = 4 * Cost(l2_cache_assoc)

#### Cache line size
Συνήθως είναι 64KB. Μπορεί η L1 να είναι πιο γρήγορη αλλά η L2 είναι πιο μεγάλη σε χωρητικότητα. Συνεπώς είναι πιο
κοστοβόρο να μεταφέρω μπλοκ στην L1 γιατί είναι περιορισμένη. Θεωρώ κόστος 4 φορές στην L1.

#### Συνεπώς συνάρτηση που προκύπτει είναι :
<pre>
Cost = 5 * l1_dcache_size * ( 4 * l1_cache_assoc + 4 * cache_line_size) + 5 * l1_icache_size * ( 4 * l1_cache_assoc + 4 * cache_line_size) + l2_cache_size * ( l2_cache_assoc+ cache_line_size)
</pre>

#### και μια πιθανή αρχιτεκτονική :

<pre>
* L1_icache_size = 64
* L1.icache.assoc = 2
* L1_dcache_size = 128
* L1.dcache.assoc = 2
* L2_cache_size = 1024
* L2.cache.assoc = 16
* cache_line_size = 64
</pre>

