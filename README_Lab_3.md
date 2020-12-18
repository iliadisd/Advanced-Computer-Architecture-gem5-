# Αρχιτεκτονική Προηγμένων Υπολογιστών
## Εργαστήριο 3Β Ομάδα 1 | Ηλιάδης-Αποστολίδης Δημοσθένης 8811

## Ερωτήματα



### 1.1 Dynamic Power and CPU Leakage

Υπάρχουν διάφοροι λόγοι που σχετίζονται με την κατανάλωση ενέργειας στον CPU. Αυτοί είναι οι εξής:
Dynamic Power Consumption, Short-Circuit Power Consumption και Power Loss λόγω Transistor Leakage Currents.

Ισχύει ότι :
<pre>
Pcpu = Pdyn + Psc + Pleak
</pre>

#### Dynamic Power
Σχετίζεται με την λειτουργία των λογικών πυλών μέσα στον επεξεργαστή. Όταν οι διακόπτες των λογικών πυλών αλλάζουν
κατάσταση, περνάει ενέργεια όσο οι πυκνωτές του κυκλώματος φορτίζονται και αποφορτίζονται. Αυτή η διαδικασία έχει
ως αποτέλεσμα την κατανάλωση ενέργειας. Ένας ακόμα παράγοντας που επηρρεάζει το Dynamic Power είναι ο Activity
Factor, ο οποίος είναι ο μέσος όρος των διάφορων switching events που γίνονται από τα transistor στο chip.
Το Dynamic Power που καταναλώνεται από έναν CPU είναι ανάλογο με τη συνολική χωρητικότητα των πυκνωτών, με το
τετράγωνο της τάσης του επεξεργαστή, με τον Activity Factor και με την συχνότητα του επεξεργαστή.
δηλαδή ισχύει ότι:

<pre>
Pdyn = C * V^2 * A * f
</pre>

#### Leakage Power
Η κατανάλωση ενέργειας που έχει να κάνει με το Leakage Power, συμβαίνει στο μικροσκοπικό επίπεδο των transistor.
Μεταξύ των διάφορων εξαρτημένων κομματιών του transistor περνάνε κάποια μικρά ρεύματα. Το πόσο μεγάλα ή μικρά θα
είναι αυτά τα ρεύματα, εξαρτάται από το state του, από τις διαστάσεις του, από διάφορα φυσικά του χαρακτηριστικά
και μερικές φορές από την θερμοκρασία. Όσο μεγαλύτερη θερμοκρασία και όσο μικρότερο είναι το transistor, τόσο
μεγαλύτερο θα είναι και το σύνολο των ρευμάτων αυτών. Χωρίζεται σε υποκατηγορίες, το subthreshold leakage,
το οποίο συμβαίνει όταν έχω ρεύμα που περνάει σε ένα transistor και αυτό είναι σε ανενεργή κατάσταση
και το gate leakage, το οποίο έχει σχέση με τη διαρροή ρεύματος στην πύλη του κάθε transistor.

Συμπερασματικά, το Dynamic Power εξαρτάται περισσότερο με τη συχνότητα του επεξεργαστή, ενώ το Leakage Power έχει
μεγαλύτερη εξάρτηση με την παρεχόμενη τάση στον επεξεργαστή.

#### Αν τρέξω διαφορετικά προγράμματα σε έναν επεξεργαστή :

Το Dynamic Runtime, το οποίο είναι η συνολική ενέργεια που απαιτείται από ένα πρόγραμμα dynamic / συνολικός χρόνος
προσομοίωσης, θα ήταν διαφορετικό γιατί κάθε φορά ο επεξεργαστής θα έκανε διαφορετικούς υπολογισμούς με
έτσι η ενέργεια θα άλλαζε, όπως και ο χρόνος εκτέλεσης. Το Peak Dynamic θα ήταν επίσης διαφορετικό, επειδή
εξαρτάται από τον μέγιστο αριθμό των switch των transistor, που θα άλλαζε σε κάθε πρόγραμμα.

Αντίθετα, η Total Leakage θα παρέμενε η ίδια καθώς σύμφωνα με την ανάλυση που έγινε παραπάνω, μιλάμε για
τον ίδιο επεξεργαστή και άρα τα ίδια transistor.

### 1.2 Σε ένα σύστημα με δύο διαφορετικούς επεξεργαστές 4W και 40W :
Για να απαντήσω στο ερώτημα θα πρέπει να σκεφτώ ποιος επεξεργαστής είναι πιο energy efficient. Το energy efficiency
ορίζεται ως :
<pre>
Energy Efficiency = Performance / Watt
</pre>
όπου το performance είναι πρακτικά τα insructions / second.

Συνεπώς αν έχω έναν επεξεργαστή που καταναλώνει 4Watt και έναν που καταναλώνει 40W, θα πρέπει να τους συγκρίνω
για ένα ίδιο benchmark και θα έπρεπε P_40W > 10 * P_4W , δηλαδή θα έπρεπε το performance του 40W επεξεργαστή
να είναι περισσότερο από 10 φορές μεγαλύτερο από το performance του 4W επεξεργαστή. Θα πρέπει δηλαδή σε κάθε
δευτερόλεπτο, να εκτελεί παραπάνω από 10 φορές τα instruction που εκτελεί ανά δευτερόλεπτο επεξεργαστής με τα
4W.

Το McPAT δε μου δίνει τις απαραίτητες πληροφορίες, όπως είναι το instruction_rate που είναι απαραίτητο για τον
υπολογισμό του performance. Αυτά θα μπορούσαν να βρεθούν από το gem5 και για ένα συγκεκριμένο benchmark/πρόγραμμα.

### 1.3 Xeon και ARM Cortex-A9 2GHz


#### Xeon
<pre>
*****************************************************************************************
  Technology 65 nm
  Using Long Channel Devices When Appropriate
  Interconnect metal projection= aggressive interconnect technology projection
  Core clock Rate(MHz) 3400

*****************************************************************************************
Processor:
  Area = 410.507 mm^2
  Peak Power = 134.938 W
  Total Leakage = 36.8319 W
  Peak Dynamic = 98.1063 W
  Subthreshold Leakage = 35.1632 W
  Subthreshold Leakage with power gating = 16.3977 W
  Gate Leakage = 1.66871 W
  Runtime Dynamic = 72.9199 W

  Total Cores: 2 cores
  Device Type= ITRS high performance device type
    Area = 111.713 mm^2
    Peak Dynamic = 78.5978 W
    Subthreshold Leakage = 24.1131 W
    Subthreshold Leakage with power gating = 10.3006 W
    Gate Leakage = 1.49026 W
    Runtime Dynamic = 55.7891 W

  Total L3s:
  Device Type= ITRS high performance device type
    Area = 293.281 mm^2
    Peak Dynamic = 6.70159 W
    Subthreshold Leakage = 10.9824 W
    Subthreshold Leakage with power gating = 6.06659 W
    Gate Leakage = 0.165767 W
    Runtime Dynamic = 4.32382 W

  Total NoCs (Network/Bus):
  Device Type= ITRS high performance device type
    Area = 5.51364 mm^2
    Peak Dynamic = 12.807 W
    Subthreshold Leakage = 0.0678232 W
    Subthreshold Leakage with power gating = 0.0305204 W
    Gate Leakage = 0.0126787 W
    Runtime Dynamic = 12.807 W

*****************************************************************************************
    </pre>

#### ARM Cortex-A9
<pre>
*****************************************************************************************
  Technology 40 nm
  Using Long Channel Devices When Appropriate
  Interconnect metal projection= conservative interconnect technology projection
  Core clock Rate(MHz) 2000

*****************************************************************************************
Processor:
  Area = 5.39698 mm^2
  Peak Power = 1.74189 W
  Total Leakage = 0.108687 W
  Peak Dynamic = 1.6332 W
  Subthreshold Leakage = 0.0523094 W
  Gate Leakage = 0.0563774 W
  Runtime Dynamic = 2.96053 W

  Total Cores: 2 cores
  Device Type= ITRS low operating power device type
    Area = 4.84735 mm^2
    Peak Dynamic = 1.57159 W
    Subthreshold Leakage = 0.0484486 W
    Gate Leakage = 0.0501375 W
    Runtime Dynamic = 1.06575 W

  Total First Level Directory:
  Device Type= ITRS low operating power device type
    Area = 0.535391 mm^2
    Peak Dynamic = 0.045212 W
    Subthreshold Leakage = 0.00370577 W
    Gate Leakage = 0.0060234 W
    Runtime Dynamic = 1.81276 W

  Total NoCs (Network/Bus):
  Device Type= ITRS low operating power device type
    Area = 0.014239 mm^2
    Peak Dynamic = 0.0164048 W
    Subthreshold Leakage = 0.000155022 W
    Gate Leakage = 0.000216526 W
    Runtime Dynamic = 0.0820239 W

*****************************************************************************************
</pre>

Για να βρω το Energy_Efficiency του κάθε επεξεργαστή, θα πρέπει να διαιρέσω το performance του κάθε επεξεργαστή
με την ισχύ που κατανάλωσε ο καθένας. υποθέτωντας, λοιπόν αμελητέα την ισχύ της πηγής στον πρώτο τύπο.
Αν x = instruction_rate_ARM είναι:
<pre>
Energy_Efficiency_ARM = x/P_dyn_ARM + x/P_leak_ARM = x/runtime_dynamic_ARM + x/total_leakage_ARM =
x / 2.96053W + x / 0.108687W = x * 9.54
</pre>

και

<pre>
Energy_Efficiency_Xeon = 40x/P_dyn_Xeon + 40x/P_leak_Xeon = 40x/runtime_dynamic_Xeon + 40x/total_leakage_Xeon =
= 40 * x / 72.9199W + 40 * x / 36.8319W = x * 1.635
</pre>

Συνεπώς :

<pre>
Energy_Efficiency_ARM = 5.835 * Energy_Efficiency_Xeon , ενδεικτικά.
</pre>

### 2.1 Energy Delay (EDP)
<pre>
*Delay = total_simulation_seconds του αρχείου stats.txt από τον gem5.
*Area -> McPAT
</pre>

Χρησιμοποιώντας το benchmark speclibm και τα αποτελέσματα του που πήρα στο προηγούμενο εργαστήριο και
χρησιμοποιώντας το print_energy.py παίρνω την τιμή του energy για κάθε τρέξιμο.

<pre>
*cache32 : energy is 267.730505 mJ

*cache128 : energy is 213.438275 mJ

*l1d64 : energy is 237.660157 mJ

*l1d128 : energy is 295.234863 mJ

*l1d_assoc2 : energy is 237.660157 mJ

*l1d_assoc4 : energy is 189.818644 mJ

*l1d_assoc8 : energy is 201.315140 mJ

*l1i64 : energy is 308.382699 mJ

*l1i128 : energy is 358.261145 mJ

*l1i_assoc2 : energy is 237.660157 mJ

*l1i_assoc4 : energy is 251.495418 mJ

*l1i_assoc8 : energy is 259.215611 mJ

*l2_256 : energy is 236.331909 mJ

*l2_2048 : energy is 237.660157 mJ

*l2_assoc4 : energy is 237.632035 mJ

*l2_assoc8 : energy is 237.660157 mJ

*speclibm_DE : energy is 210.371373 mJ
</pre>

Παρατηρώ ότι ισχύει :
<pre>
*energy = (runtime_dynamic+total_leakage) * simulation_time
</pre>
Παρατηρώ επίσης ότι η επιλογή που έκανα στο Design Exploration του προηγούμενου εργαστηρίου καταφέρνει να
θέλει λιγότερο energy από κάθε απλή αλλαγή κάποιας παραμέτρου.

### 2.2 Επίδραση των παραμέτρων για Peak Power και Area

Μορφοποιήσαμε καταλλήλως τα scripts συμφωνα με τις οδηγίες και τρέξαμε simulations για το benchmark bzip.
Βλέπουμε παρακάτω τα σχετικά διαγράμματα που προκύπτουν.

#### cache_line_size

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab3/photos/cache.png?raw=true)

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab3/photos/cache_data.png?raw=true)

#### l1_dcache_size

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab3/photos/l1dcache.png?raw=true)

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab3/photos/l1dcache_data.png?raw=true)

#### l1_dcache_assoc

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab3/photos/l1dcache_assoc.png?raw=true)

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab3/photos/l1dcache_assoc_data.png?raw=true)

#### l1_icache_size

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab3/photos/l1icache.png?raw=true)

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab3/photos/l1icache_data.png?raw=true)

#### l1_icache_assoc

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab3/photos/l1icache_assoc.png?raw=true)

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab3/photos/l1icache_assoc_data.png?raw=true)

#### l2_cache_size

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab3/photos/l2cache.png?raw=true)

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab3/photos/l2cache_data.png?raw=true)

#### l2_cache_assoc

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab3/photos/l2cache_assoc.png?raw=true)

![image](https://github.com/iliadisd/gem5_Lab/blob/main/Lab3/photos/l2cache_assoc_data.png?raw=true)

### Διαφορετικά αποτελέσματα και αποκλίσεις
Διαβάζοντας το το άρθρο που αναφέρεται και στα resources, καταλήγω στο συμπέρασμα ότι τα σφάλματα και οι αποκλίσεις
στα αποτελέσματα που πήρα προκύπτουν από 2 παράγοντες. Πρώτον ο συνδυασμός των αποτελεσμάτων από το McPAT και
το gem5 από το κάθε πρόγραμμα ξεχωριστό το οποίο εισάγει με τους διάφορους υπολογισμούς που κάνει, αλλά και
δεύτερον  φέρνει ακόμα μεγαλύτερο σφάλμα η διαφορετική μεθοδολογία που μπορεί να ακολουθεί κάθε πρόγραμμα στον τρόπο
που κάνει τα simulation ή τους υπολογισμούς του. Τέλος, ένας άλλος λόγος είναι ο συνδυασμός διάφορων αποτελεσμάτων
και η πράξη μεταξύ διάφορων αριθμών που μπορεί να στρογγυλοποιούνται με λάθος τρόπο.

*Resources:*
https://en.wikipedia.org/wiki/CPU_power_dissipation
https://en.wikipedia.org/wiki/Dynamic_frequency_scaling
https://www.princeton.edu/~mrm/tutorial/hpca2001_tutorial.pdf
https://www.eecs.umich.edu/courses/eecs470/OLD/w14/lectures/470L14W14.pdf
https://www.sciencedirect.com/topics/computer-science/static-power
https://en.wikipedia.org/wiki/Power%E2%80%93delay_product
https://en.wikipedia.org/wiki/CPU_cache
https://research.cs.wisc.edu/vertical/papers/2014/wddd-sim-harmful.pdf

#### Κριτική/Παρατηρήσεις
Αυτό το εργαστήριο είχε αρκετό ενδιαφέρον σχετικά με το ενεργειακό κομμάτι στην λειτουργία των CPU. Ίσως το πιο
ενδιαφέρον κομμάτι είναι το πώς θα μπορέσει να βελτιωθεί η διαδικασία του συνδυασμού διαφόρων αποτελεσμάτων από
διαφορετικά performance simulator ή και από άλλα προγράμματα όπως το McPAT. Ίσως ο συνδυασμός σε πλατφόρμες
ενιαίες οι οποίες θα μπορούν να βγάζουν όλα τα απαραίτητα αποτελέσματα συνδυαστικά να είναι μονόδρομος, για την
καλύτερη μελέτη και άντληση συμπερασμάτων της αρχιτεκτονικής υπολογιστών και της αποτελεσματικότητάς της, σε όλα
τα επίπεδα (energy, performance, κόστος,..).
