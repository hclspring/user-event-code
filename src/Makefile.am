bin_PROGRAMS=preprocess clique_offline clique_online cut_offline cut_online compute_cost_to_file compute_cost_to_screen cut_online_specific_arrival exhaustive_offline simulated_annealing_offline online_greedy onlineF_greedy offline_FDTA PDTA usereventjob
INCLUDES = -I/usr/local/include/igraph
#bin_PROGRAMS=preprocess test

preprocess_LDADD=-ligraph
preprocess_LDFLAGS=-static
preprocess_SOURCES=preprocess.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc Config.h Config.cc

test_SOURCES=test.cc

clique_offline_LDADD=-ligraph
clique_offline_LDFLAGS=-static
clique_offline_SOURCES=clique_offline.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc Config.h Config.cc

clique_online_LDADD=-ligraph
clique_online_LDFLAGS=-static
clique_online_SOURCES=clique_online.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc Config.h Config.cc

cut_offline_LDADD=-ligraph
cut_offline_LDFLAGS=-static
cut_offline_SOURCES=cut_offline.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc Config.h Config.cc

cut_online_LDADD=-ligraph
cut_online_LDFLAGS=-static
cut_online_SOURCES=cut_online.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc Config.h Config.cc

cut_online_specific_arrival_LDADD=-ligraph
cut_online_specific_arrival_LDFLAGS=-static
cut_online_specific_arrival_SOURCES=cut_online_specific_arrival.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc Config.h Config.cc

exhaustive_offline_LDADD=-ligraph
exhaustive_offline_LDFLAGS=-static
exhaustive_offline_SOURCES=exhaustive_offline.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc Config.h Config.cc

simulated_annealing_offline_LDADD=-ligraph
simulated_annealing_offline_LDFLAGS=-static
simulated_annealing_offline_SOURCES=simulated_annealing_offline.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc Config.h Config.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc

compute_cost_to_file_LDADD=-ligraph
compute_cost_to_file_LDFLAGS=-static
compute_cost_to_file_SOURCES=compute_cost_to_file.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc Config.h Config.cc

compute_cost_to_screen_LDADD=-ligraph
compute_cost_to_screen_LDFLAGS=-static
compute_cost_to_screen_SOURCES=compute_cost_to_screen.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc Config.h Config.cc

online_greedy_LDADD=-ligraph
online_greedy_LDFLAGS=-static
online_greedy_SOURCES=online_greedy.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc Config.h Config.cc

onlineF_greedy_LDADD=-ligraph
onlineF_greedy_LDFLAGS=-static
onlineF_greedy_SOURCES=onlineF_greedy.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc Config.h Config.cc

offline_FDTA_LDADD=-ligraph
offline_FDTA_LDFLAGS=-static
offline_FDTA_SOURCES=offline_FDTA.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc Config.h Config.cc

PDTA_LDADD=-ligraph
PDTA_LDFLAGS=-static
PDTA_SOURCES=PDTA.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc Config.h Config.cc

usereventjob_LDADD=-ligraph
usereventjob_LDFLAGS=-static
usereventjob_SOURCES=main.cc Process.cc Process.h User.cc User.h Event.cc Event.h Util.cc Util.h MarginalGainHeap.h MarginalGainHeap.cc MarginalGain.h MarginalGain.cc UserEventBase.h UserEventBase.cc UtilIgraph.h UtilIgraph.cc Config.h Config.cc RunnerManager.h Runner.h Constant.h UtilConstant.h UtilConstant.cc Parameter.h Parameter.cc StepPreprocess.h StepPreprocess.cc StepCalcAssignment.h StepCalcAssignment.cc StepCalcMatch.h StepCalcMatch.cc StepCalcCost.h StepCalcCost.cc StepNormalize.h StepNormalize.cc

