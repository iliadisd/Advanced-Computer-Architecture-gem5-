# Αρχιτεκτονική Προηγμένων Υπολογιστών
## Εργαστήριο 1Β Ομάδα 1 | Ηλιάδης-Αποστολίδης Δημοσθένης 8811

## Ερωτήματα


### 1) Στη main() της starter_se.py:
<pre>

* Default CPU type = atomic
* Default CPU frequency = 4 Ghz
* Default CPU Cores to utilize = 1 core
* Default Memory type = DDR3_1600_8x8
* Default Memory channels = 2
* Default Memory Ranks = 2
* Default Memory Size = 2 GB
* Cache line size = 64 bytes

</pre>

### 2a) Τα config.ini και config.json είναι τα ίδια αρχεία απλά σε άλλο format. Τα αποτελέσματα διαφέρουν λίγο, πράγμα λογικό αφού στην εκτέλεση χρησιμοποιήσαμε το --cpu="minor" flag, αντί του atomic.
<pre>

* type=MinorCPU
* numThreads=1        
* ranks_per_channel=2
* cache_line_size = 64
* voltage=3.3
* p_state_clk_gate_max=1000000000000

</pre>

### 2b) Committed instructions. Στο stats.txt για το hello world έχουμε 54 calls σε commited instruction classes. Η διαφορά οφείλεται σε διάφορα microperations που κάνει το gem5.
<pre>

* system.cpu_cluster.cpus.committedInsts           5028
* system.cpu_cluster.cpus.committedOps             5834

</pre>

### 2c) Αν δεν είχαμε τα στατιστικά θα προσπαθούσα να βρω από το L1 τα misses/missrate = memory accesses. Τα L2 cache accesses :
<pre>

* system.cpu_cluster.l2.overall_accesses::total    479

</pre>

### 3) Cpu models of gem5.
<pre>

Το gem5 χρησιμοποιεί διάφορα CPU models. Τα βασικά in-order CPU models που χρησιμοποιεί είναι το SimpleCPU και το MinorCPU.

Το SimpleCPU χρησιμοποιείται συνήθως, όταν δε χρειαζόμαστε ένα λεπτομερές μοντέλο. Ένα παράδειγμα χρήσης του, είναι να 
δούμε απλά ότι το πρόγραμμά μας λειτουργεί. Χωρίζεται σε τρεις κλάσεις πλέον : Το BaseSimpleCPU, το AtomicSimpleCPU και
το TimingSimpleCPU.

Το BaseSimpleCPU δεν τρέχει από μόνο του. Χρειάζεται να τρέξει μαζί με ένα AtomicSimpleCPU ή ένα TimingSimpleCPU ούτως 
ώστε τα τελευταία να χρησιμοποιήσουν κάποια χαρακτηριστικά του. Το BaseSimpleCPU μπορεί να αξιοποιηθεί για μια σειρά 
από λειτουργίες όπως να ορίσει συναρτήσεις για interrupts, να κάνει το pre-execute setup και διάφορα post-execute actions
και να προχωράει τον PC σε επόμενα instructions. Τέλος υλοποιεί το ExecContext interface που μπορεί να χρησιμοποιηθεί 
για διάφορες βασικές λειτουργίες όπως R/W int,float και control registers, R/W memory και άλλα.

Το AtomicSimpleCPU χρησιμοποιεί atomic memory accesses. Όταν αυτές γίνονται, οι απαντήσεις γυρνάνε μέσα από τα function
returns. Χρησιμοποιούνται για fast forwarding και για να κάνοτν warm up τις caches και γυρνάνε μια χρονική εκτίμηση για
την ολοκλήρωση του request χωρίς delays. Το AtomicSimpleCPU χρησιμοποιεί αυτούς τους χρόνους για να μπορέσει να εκτιμήσει
ένα overall συνολικό cache access time. Τέλος, το AtomicSimpleCPU υλοποιεί συναρτήσεις για το R/W memory, για τα ticks και
συνδέει τη CPU με την cache.

Το TimingSimpleCPU χρησιμοποιεί timing memory accesses. Αυτές είναι οι πιο λεπτομερείς προσπελάσεις και μοντελοποιούν μία
πιο ρεαλιστική προσομοίωση (με delays κλπ). Είναι πιο αργές από τις atomic memory accesses και δεν μπορούν να συνυπάρξουν
μεταξύ τους. Το TimingSimpleCPU καθυστερεί στα cache accesses και περιμένει το memory system να απαντήσει πριν να προχωρήσει.
Το TimingSimpleCPU υλοποιεί τις ίδιες  συναρτήσεις με το AtomicSimpleCPU και συνδέει τη CPU με την cache. Τέλος μπορεί να 
ορίσει τις απαραίτητες συναρτήσεις για τη διαχείρηση της όλης διαδικασίας από το response της μνήμης μέχρι τις προσπελάσεις
και τις επιστροφές τους.

Πέρα από το SimpleCPU υπάρχει και το MinorCPU model. Το MinorCPU είναι ένα in-order CPU μοντέλο με fixed pipeline αλλά με
configurable data structures και συμπεριφορά εκτέλεσης. Το πιο σημαντικό χαρακτηριστικό του MinorCPU είναι τα Pipeline 
Stages. Το κάθε Pipeline Stage είναι υπεύθυνο για πράξεις όπως αποκωδικοποίηση ή εκτέλεση κάποιας εντολής και εάν η 
λειτουργία του ήταν επιτυχής και το επόμενο στάδιο είναι έτοιμο να δεχθεί εντολές τότε στέλνει instructions στο επόμενο
stage αλλιώς κρατάει την πληροφορία περιμένοντας να τηρούνται οι παραπάνω προϋποθέσεις. Τα stages επικοινωνούν μεταξύ τους
για 3 λόγους. Είτε για να στείλουν instructions στα επόμενα stages, είτε όταν υπάρχει κάποιο πρόβλημα στη ροή για να τη
σταματήσουν στα προηγούμενα stages ή όταν έχει γίνει κάποιο λάθος στην αλληλουχία των stages. Συνήθως τα stages 
χρησιμοποιούνται σε πεντάδες με τις εξής λειτουργίες:
εισαγωγή εντολής -> αποκωδικοποίηση εντολής -> εκτέλεση εντολής -> επεξεργασία μνήμης -> εγγραφή καταχωρητών

</pre>

### 3a) C code
<pre>

    #include "stdio.h"

    int main () {
      int i, sum = 0;
      //float n;
      printf("\nSum Calculator from 1 to 100 \n \n");

      /* I didn't use this after all for simplicity reasons
      do {
           printf("Please enter a natural number N : ");
           scanf("%f", &n);
      } while (n <= 0);
      */

      for(i = 1; i <= 100 ; ++i) {
        sum += i;
      }
      printf("sum = %d \n \n", sum) ;
      return 0;
     }

</pre>

#### i) *MinorCPU*
<pre>
* final_tick                                   36814000                       # Number of ticks from beginning of simulation (restored from checkpoints and never reset)
* host_inst_rate                                 266201                       # Simulator instruction rate (inst/s)
* host_mem_usage                                 666432                       # Number of bytes of host memory used
* host_op_rate                                   304458                       # Simulator op (including micro ops) rate (op/s)
* host_seconds                                     0.04                       # Real time elapsed on the host
* host_tick_rate                              862346686                       # Simulator tick rate (ticks/s)
* sim_freq                                 1000000000000                       # Frequency of simulated ticks
* sim_insts                                       11347                       # Number of instructions simulated
* sim_ops                                         12994                       # Number of ops (including micro ops) simulated
* sim_seconds                                  0.000037                       # Number of seconds simulated
* sim_ticks                                    36814000  
</pre>
#### ii) *TimingSimpleCPU*
<pre>
* final_tick                                   43585000                       # Number of ticks from beginning of simulation (restored from checkpoints and never reset)
* host_inst_rate                                 718875                       # Simulator instruction rate (inst/s)
* host_mem_usage                                 664128                       # Number of bytes of host memory used
* host_op_rate                                   817889                       # Simulator op (including micro ops) rate (op/s)
* host_seconds                                     0.02                       # Real time elapsed on the host
* host_tick_rate                             2766543291                       # Simulator tick rate (ticks/s)
* sim_freq                                 1000000000000                       # Frequency of simulated ticks
* sim_insts                                       11281                       # Number of instructions simulated
* sim_ops                                         12877                       # Number of ops (including micro ops) simulated
* sim_seconds                                  0.000044                       # Number of seconds simulated
* sim_ticks                                    43585000

</pre>

### 3b) Όπως αναφέρθηκε και παραπάνω, το μοντέλο TimingSimpleCPU χρησιμοποιεί timing memory accesses που είναι πιο αργό πιο detailed access και απαιτούνται πολλαπλοί κύκλοι απ'ότι το MinorCPU.

### 3c) Δοκιμές


#### i) *MinorCPU* @ 3.7GHz
<pre>
* final_tick                                   32743000                       # Number of ticks from beginning of simulation (restored from checkpoints and never reset)
* host_inst_rate                                 263634                       # Simulator instruction rate (inst/s)
* host_mem_usage                                 666176                       # Number of bytes of host memory used
* host_op_rate                                   301527                       # Simulator op (including micro ops) rate (op/s)
* host_seconds                                     0.04                       # Real time elapsed on the host
* host_tick_rate                              759618184                       # Simulator tick rate (ticks/s)
* sim_freq                                 1000000000000                       # Frequency of simulated ticks
* sim_insts                                       11347                       # Number of instructions simulated
* sim_ops                                         12994                       # Number of ops (including micro ops) simulated
* sim_seconds                                  0.000033                       # Number of seconds simulated
* sim_ticks                                    32743000                       # Number of ticks simulated
</pre>
#### ii) *TimingSimpleCPU* @ 3.7GHz
<pre>

* final_tick                                   39575500                       # Number of ticks from beginning of simulation (restored from checkpoints and never reset)
* host_inst_rate                                 706742                       # Simulator instruction rate (inst/s)
* host_mem_usage                                 664128                       # Number of bytes of host memory used
* host_op_rate                                   804076                       # Simulator op (including micro ops) rate (op/s)
* host_seconds                                     0.02                       # Real time elapsed on the host
* host_tick_rate                             2467125462                       # Simulator tick rate (ticks/s)
* sim_freq                                 1000000000000                       # Frequency of simulated ticks
* sim_insts                                       11281                       # Number of instructions simulated
* sim_ops                                         12877                       # Number of ops (including micro ops) simulated
* sim_seconds                                  0.000040                       # Number of seconds simulated
* sim_ticks                                    39575500                       # Number of ticks simulated
</pre>
Βλέπουμε και στις 2 περιπτώσεις ότι αυξάνοντας τη συχνότητα μειώνεται ο χρόνος, πράγμα αναμενόμενο.

#### iii) *MinorCPU* with DDR3_2133_8x8
<pre>

* final_tick                                   35420000                       # Number of ticks from beginning of simulation (restored from checkpoints and never reset)
* host_inst_rate                                 269319                       # Simulator instruction rate (inst/s)
* host_mem_usage                                 666176                       # Number of bytes of host memory used
* host_op_rate                                   308020                       # Simulator op (including micro ops) rate (op/s)
* host_seconds                                     0.04                       # Real time elapsed on the host
* host_tick_rate                              839410647                       # Simulator tick rate (ticks/s)
* sim_freq                                 1000000000000                       # Frequency of simulated ticks
* sim_insts                                       11347                       # Number of instructions simulated
* sim_ops                                         12994                       # Number of ops (including micro ops) simulated
* sim_seconds                                  0.000035                       # Number of seconds simulated
* sim_ticks                                    35420000  

</pre>

#### iv) *TimingSimpleCPU* with DDR3_2133_8x8
<pre>

* final_tick                                   42606000                       # Number of ticks from beginning of simulation (restored from checkpoints and never reset)
* host_inst_rate                                 690842                       # Simulator instruction rate (inst/s)
* host_mem_usage                                 664132                       # Number of bytes of host memory used
* host_op_rate                                   786258                       # Simulator op (including micro ops) rate (op/s)
* host_seconds                                     0.02                       # Real time elapsed on the host
* host_tick_rate                             2599844532                       # Simulator tick rate (ticks/s)
* sim_freq                                 1000000000000                       # Frequency of simulated ticks
* sim_insts                                       11281                       # Number of instructions simulated
* sim_ops                                         12877                       # Number of ops (including micro ops) simulated
* sim_seconds                                  0.000043                       # Number of seconds simulated
* sim_ticks                                    42606000   

</pre>

Παρατηρούμε ότι και με πιο μεγάλη συχνότητα στη μνήμη βελτιώνεται η ταχύτητα.

#### v) *MinorCPU* @ 3.7GHz & DDR3_2133_8x8
<pre>

* final_tick                                   31525000                       # Number of ticks from beginning of simulation (restored from checkpoints and never reset)
* host_inst_rate                                 266937                       # Simulator instruction rate (inst/s)
* host_mem_usage                                 666180                       # Number of bytes of host memory used
* host_op_rate                                   305313                       # Simulator op (including micro ops) rate (op/s)
* host_seconds                                     0.04                       # Real time elapsed on the host
* host_tick_rate                              740548342                       # Simulator tick rate (ticks/s)
* sim_freq                                 1000000000000                       # Frequency of simulated ticks
* sim_insts                                       11347                       # Number of instructions simulated
* sim_ops                                         12994                       # Number of ops (including micro ops) simulated
* sim_seconds                                  0.000032                       # Number of seconds simulated
* sim_ticks                                    31525000      

</pre>

#### vi) *TimingSimpleCPU* @ 3.7GHz & DDR3_2133_8x8
<pre>

* final_tick                                   38330500                       # Number of ticks from beginning of simulation (restored from checkpoints and never reset)
* host_inst_rate                                 718534                       # Simulator instruction rate (inst/s)
* host_mem_usage                                 664132                       # Number of bytes of host memory used
* host_op_rate                                   817519                       # Simulator op (including micro ops) rate (op/s)
* host_seconds                                     0.02                       # Real time elapsed on the host
* host_tick_rate                             2431826323                       # Simulator tick rate (ticks/s)
* sim_freq                                 1000000000000                       # Frequency of simulated ticks
* sim_insts                                       11281                       # Number of instructions simulated
* sim_ops                                         12877                       # Number of ops (including micro ops) simulated
* sim_seconds                                  0.000038                       # Number of seconds simulated
* sim_ticks                                    38330500     

</pre>

*Resources:*
http://gem5.org/Running_gem5
https://www.gem5.org/documentation/general_docs/cpu_models/SimpleCPU
https://www.gem5.org/documentation/general_docs/cpu_models/minor_cpu
https://www.gem5.org/documentation/general_docs/memory_system/index.html#access-types
https://www.gem5.org/documentation/general_docs/cpu_models/execution_basics
http://learning.gem5.org/book/part1/gem5_stats.html
http://learning.gem5.org/book/part1/building.html
http://learning.gem5.org/book/part1/example_configs.html
https://nitish2112.github.io/post/gem5-minor-cpu/

#### Κριτική/Παρατηρήσεις
<pre>
Για να μην μακρυγορώ, προσωπικά θεωρώ ότι τα πιο υποσχόμενα κομμάτια αναφορικά με το gem5 είναι δύο πράγματα.
Πρώτον το πόσο μπορούμε να πειράζουμε τα simulation scripts που είναι γραμμένα σε python, η ακόμα ακόμα να γράφουμε
δικά μας. Αυτό ίσως θα μπορούσαμε να δοκιμάζουμε και λειτουργηικά συστήματα ολόκληρα σε
simulation ακόμα και για συνθέσεις που δεν κυκλοφορούν ακόμα στην αγορά (pre-release performance simulation χωρίς
καν το hardware). Τέλος το δεύτερο σημαντικό κομμάτι θεωρώ πως είναι η δοκιμή παράλληλου προγραμματισμού και threads
σε διάφορα simulation scripts για να μπορούμε να βλέπουμε διαφορά στο performance στο αντίστοιχο hardware.
</pre>


