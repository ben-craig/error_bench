#!/usr/bin/env python
import statistics
import pandas as pd
# plat -> {frames, {plat_name, {case_name, [[val]]}}}

COLORS = [
  "1b9e77",
  "d95f02",
  "7570b3",
  "e7298a",
  "66a61e",
  "e6ab02",
  "a6761d",
  "666666",
]

CPU_FREQ = 3.3915
START_PIX = 20
PIX_HEIGHT=20

PLAT_ORDER = [
  "gcc",
  "clang",
  "MSVC_c64",
  "MSVC_x64",
  "MSVC_x86",
]

CASE_ORDER = [
  "throw_exception",
  "throw_struct",
  "throw_val",
  "noexcept_terminate",
  "terminate",
  "noexcept_abort",
  "abort",
  "alt_return",
  "return_val",
  "ref_struct",
  "return_nt_struct",
  "return_struct",
  "expected_struct",
  "outcome_std_error",
]
def dict_maker(l):
  dict = {}
  for i in range(len(l)):
    dict[l[i]] = i
  return dict

CASE_ORDER_DICT = dict_maker(CASE_ORDER)
PLAT_ORDER_DICT = dict_maker(PLAT_ORDER)
def case_group_sorter(case_group):
  case_name, _ = case_group
  return CASE_ORDER_DICT[case_name]

def plat_case_sorter(plat_case_group):
  idx, _ = plat_case_group
  plat_name, case_name = idx
  return PLAT_ORDER_DICT[plat_name] * len(CASE_ORDER_DICT) + CASE_ORDER_DICT[case_name]

def plat_group_sorter(plat_group):
  plat_name, _ = plat_group
  return PLAT_ORDER_DICT[plat_name]

def calc_bucket(value, width):
  return round(value/width, 0) * width

def bucket_data(hist, value, width):
  bucket = calc_bucket(value, width)
  count = hist.setdefault(bucket, 0)
  hist[bucket] = count+1
  return bucket

def emit_boilerplate(fout):
  fout.write("var commonGrid = {\n")
  fout.write("  show: false,\n")
  fout.write("  left: 200,\n")
  fout.write("  right: '3%',\n")
  fout.write("  height: " + str(PIX_HEIGHT) + ",\n")
  fout.write("}\n")

def aesthetic_round(val):
  as_str = "{:.2e}".format(val)
  lead_digit = as_str[0]
  new_lead = {
    '0' : '0',
    '1' : '2',
    '2' : '5',
    '3' : '5',
    '4' : '5',
    '5' : '1',
    '6' : '1',
    '7' : '1',
    '8' : '1',
    '9' : '1',
  }[lead_digit]

  as_list = list(as_str)
  as_list[0] = new_lead
  as_list[2] = '0'
  as_list[3] = '0'
  new_width = float("".join(as_list))
  if new_lead == '1':
    new_width = 10.0 * new_width
  return new_width

MAX_DESIRED_BUCKETS = 150.0
def calc_width(min_x, max_x):
  start_width = float(max_x - min_x) / MAX_DESIRED_BUCKETS
  return aesthetic_round(start_width)

def emit_row(fout, case_tuple, value):
  data_str = "{:.2f}".format(value)
  fout.write("  '" + str.join(".", case_tuple) + "': " + data_str + ",\n")

def emit_stats(fout, df):
  groups = df.groupby(['plat', 'case', 'mood'])
  fout.write("var means = {\n")
  for group in groups:
    emit_row(fout, group[0], statistics.mean(group[1].time))
  fout.write("};\n")

  fout.write("var medians = {\n")
  for group in groups:
    emit_row(fout, group[0], statistics.median(group[1].time))
  fout.write("};\n")

  fout.write("var stdevs = {\n")
  for group in groups:
    emit_row(fout, group[0], statistics.stdev(group[1].time))
  fout.write("};\n")

  fout.write("var variances = {\n")
  for group in groups:
    emit_row(fout, group[0], statistics.variance(group[1].time))
  fout.write("};\n")

def emit_violin_data(fout, modifier, df):
  fout.write("var " + modifier + "violin_data = {\n")

  for mood, mood_data in df.groupby('mood'):
    fout.write("  " + mood + ": {\n")
    width = calc_width(min(mood_data.time), max(mood_data.time))
    for plat, plat_data in mood_data.groupby('plat'):
      fout.write("    " + plat + ": {\n")
      for case, data in plat_data.groupby('case'):
        fout.write("      " + case + ": [\n")
        hist = {}
        for value in data.time:
          bucket_data(hist, value, width)
        for val, count in sorted(hist.items()):
          fout.write("        [" + "{:.2f}".format(val) + ", " + str(count) + "],\n")
        fout.write("      ],\n")
      fout.write("    },\n")
    fout.write("  },\n")
  fout.write("};\n\n")

def emit_grids(fout, df):
  top = START_PIX
  fout.write("  grid: [\n")
  for i in range(len(df.groupby(['plat', 'case']))):
    mid = top + PIX_HEIGHT
    fout.write("    Object.assign({top: " + str(top) + "}, commonGrid),\n")
    fout.write("    Object.assign({top: " + str(mid) + "}, commonGrid),\n")
    top = mid + PIX_HEIGHT
  fout.write("  ],\n")
  fout.write("  gridHeight: " + str(top) + ",\n")

def emit_xAxis(fout, df):
  fout.write("  xAxis: [\n")
  idx = 0
  showAxis = "false"

  the_min = min(df.time)
  the_max = max(df.time)
  width = calc_width(the_min, the_max)
  bucketed_min = str(calc_bucket(the_min, width))
  bucketed_max = str(calc_bucket(the_max, width))
  min_max = bucketed_min + ", " + bucketed_max

  row_groups = df.groupby(['plat','case'])
  for row_name, row_data in sorted(row_groups, key=plat_case_sorter):
    name = str.join(".",row_name)
    if idx == len(row_groups)-1:
      showAxis = "true"
    fout.write("    make_xAxis('" + name + "', " + str(2*idx) +", false, " + min_max + "),\n")
    fout.write("    make_xAxis('" + name + "', " + str(2*idx+1) +", " + showAxis + ", " + min_max + "),\n")
    idx = idx + 1
  fout.write("  ],\n")

def emit_yAxis(fout, df):
  fout.write("  yAxis: [\n")
  for i in range(len(df.groupby(['plat','case']))):
    fout.write("    Object.assign({gridIndex: " + str(2*i) + "}, commonYAxis),\n")
    fout.write("    Object.assign({gridIndex: " + str(2*i+1) + "}, invertYAxis),\n")
  fout.write("  ],\n")

def emit_series(fout, modifier, mood, df):
  fout.write("  series: [\n")
  idx = 0
  groups = df.groupby(['plat','case'])
  for ident, data in sorted(groups, key=plat_case_sorter):
    name = str.join(".",ident)
    dataStr = modifier + "violin_data." + mood + "." + name #TODO
    color = COLORS[idx % len(COLORS)]
    fout.write("    make_series( '" +name + "', " + str(2*idx) + ", " + dataStr + ", '#" + color + "'),\n")
    fout.write("    make_series( '" +name + "', " + str(2*idx+1) + ", " + dataStr + ", '#" + color + "'),\n")
    idx = idx + 1
  fout.write("  ],\n")

def emit_violin_formatters(fout, df):
  mood_groups = df.groupby('mood')
  for mood, data in mood_groups:
    fout.write("function " + mood + "_violin_formatter(params, ticket, callback) {\n")
    fout.write("  return violin_formatter_impl(\"" + mood + "\", params, ticket, callback);\n")
    fout.write("}\n")

def emit_bar_formatters(fout, df):
  mood_groups = df.groupby('mood')
  for mood, data in mood_groups:
    fout.write("function " + mood + "_bar_formatter(params, ticket, callback) {\n")
    fout.write("  return bar_formatter_impl(\"" + mood + "\", params, ticket, callback);\n")
    fout.write("}\n")

def emit_violins(fout, modifier, df):
  emit_violin_data(fout, modifier, df)
  mood_groups = df.groupby('mood')
  for mood, data in mood_groups:
    fout.write("var violin_" + modifier + mood + " = {\n")
    fout.write("  tooltip : { formatter: " + mood + "_violin_formatter },\n")
    emit_grids(fout, data)
    emit_xAxis(fout, data)
    emit_yAxis(fout, data)
    emit_series(fout, modifier, mood, data)
    fout.write("};\n\n")

def emit_all_violins(fout, df):
  emit_violin_formatters(fout, df)
  happy_df = df[(df.mood == "happy") | (df.mood == "happy_param") | (df.mood == "happy_ret")]
  sad_df = df[(df.mood == "sad") | (df.mood == "sad_param") | (df.mood == "sad_ret")]
  reduced_sad_df = sad_df[(sad_df.case == "throw_exception") | (sad_df.case == "return_val")]
  noexcept_sad_df = sad_df[~(sad_df.case == "throw_exception")]
  emit_violins(fout, "", happy_df)
  emit_violins(fout, "reduced_sad_", reduced_sad_df)
  emit_violins(fout, "noexcept_sad_", noexcept_sad_df)

def emit_bar_yAxis(fout, df):
  fout.write("var barYAxisData = [\n")
  plat_groups = df.groupby('plat')
  for plat, data in sorted(plat_groups, key=plat_group_sorter):
    fout.write("  '" + plat + "',\n")
  fout.write("];\n")

def emit_bar_series(fout, mood, df):
  case_groups = df.groupby('case')
  fout.write("  series: [\n")
  idx = 0
  for case, case_data in sorted(case_groups, key=case_group_sorter):
    fout.write("    {\n")
    fout.write("      type: 'bar',\n")
    fout.write("      name: '" + case + "',\n")
    fout.write("      itemStyle: {color: '#" + COLORS[idx] + "'},\n")
    fout.write("      data: [\n")
    plat_groups = case_data.groupby('plat')
    for plat, plat_data in sorted(plat_groups, key=plat_group_sorter):
      fout.write("        medians['" + plat + "." + case + "." + mood + "'],\n")
    fout.write("      ],\n")
    fout.write("    },\n")
    idx = idx + 1
    if idx == len(COLORS):
      idx = 0
  fout.write("  ],\n")

def emit_bars(fout, modifier, df):
  mood_groups = df.groupby('mood')

  boilerplate = """
  calculable : true,
  legend: {
    right: 0,
    top: 0,
    orient: 'vertical',
  },
  xAxis: [{
    type: 'value'
  }],
  grid: {
    top: 0,
    left: 80,
    right: 150,
  },
  yAxis: [{
    type: 'category',
    inverse:true,
    data: barYAxisData
  }],
"""

  emit_bar_yAxis(fout, df)
  for mood, data in mood_groups:
    fout.write("var bar_" + modifier + mood + " = {\n")
    fout.write("  tooltip : { formatter: " + mood + "_bar_formatter },\n")
    emit_bar_series(fout, mood, data)
    fout.write(boilerplate)
    fout.write("};\n\n")

def emit_all_bars(fout, df):
  emit_bar_formatters(fout, df)

  happy_df = df[(df.mood == "happy") | (df.mood == "happy_param") | (df.mood == "happy_ret")]
  reduced_happy_df = happy_df[(happy_df.case == "alt_return") | (happy_df.case == "throw_exception") | (happy_df.case == "abort") | (happy_df.case == "return_val")]

  sad_df = df[(df.mood == "sad") | (df.mood == "sad_param") | (df.mood == "sad_ret")]
  reduced_sad_df = sad_df[(sad_df.case == "alt_return") | (sad_df.case == "throw_exception") | (sad_df.case == "return_val")]
  noexcept_sad_df = sad_df[~(sad_df.case == "throw_exception")]

  emit_bars(fout, "", happy_df)
  emit_bars(fout, "reduced_", reduced_happy_df)
  emit_bars(fout, "reduced_sad_", reduced_sad_df)
  emit_bars(fout, "noexcept_sad_", noexcept_sad_df)

def emit_single_js(fout, df):
  fout.write(JS_HEADER)
  emit_boilerplate(fout)
  emit_stats(fout, df)
  emit_all_violins(fout, df)
  emit_all_bars(fout, df)

def main():
  df = pd.read_csv('gauss_times.csv')

  df = df[(df.mood != "happy_ret_nd") & (df.mood != "sad_ret_nd")]
  is_sad_terminate = ((df.case == "abort") & ( (df.mood == "sad") | (df.mood == "sad_ret") | (df.mood == "sad_param")))
  df = df[~is_sad_terminate]
  df.time = df.time * CPU_FREQ

  with open("data.js", 'w') as fout:
    emit_single_js(fout, df)



JS_HEADER = """
var commonYAxis = {
  splitLine: { show: false },
  axisLine:  { show: false },
  axisTick:  { show: false },
  axisLabel: { show: false },
}
var invertYAxis = Object.assign(
  {
    inverse:true,
    position: 'top'
  },
  commonYAxis)

function make_xAxis(name, idx, axisLabel, min, max) {
  if (idx == 0)
  {
    return {
      name: name,
      gridIndex: 0,
      axisLine:  { show: false },
      axisTick:  { show: false },
      axisLabel: { show: true, inside: true, verticalAlign: 'bottom' },
      nameLocation: "start",
      min: min,
      max: max,
    };
  }

  return   {
    name: name,
    gridIndex: idx,
    axisLine:  { show: false },
    axisTick:  { show: false },
    axisLabel: { show: axisLabel },
    nameLocation: "start",
    min: min,
    max: max,
  };
}
function make_series(name, idx, data, color) {
  return {
    name: name,
    xAxisIndex: idx,
    yAxisIndex: idx,
    itemStyle: {color: color},
    data: data,
    barWidth: 4,
    type: 'bar',
  };
}
function violin_formatter_impl(mood, params, ticket, callback) {
  stat_key = params.seriesName + "." + mood;
  mean = means[stat_key];
  median = medians[stat_key];
  stdev = stdevs[stat_key];
  variance = variances[stat_key];
  return params.seriesName + "<br />" +
    params.value[0] + " cycles, " + params.value[1] + " samples" + "<br />" +
    "median: " + median + " cycles, mean: " + mean + " cycles"  + "<br />" +
    "stdev: " + stdev + " cycles, variance: " + variance + " cycles";
}

function bar_formatter_impl(mood, params, ticket, callback) {
  id = params.name + "." + params.seriesName;
  idx = id + "." + mood
  mean = means[idx];
  median = medians[idx];
  stdev = stdevs[idx];
  variance = variances[idx];
  return id + "<br />" +
    "median: " + median + " cycles, mean: " + mean + " cycles"  + "<br />" +
    "stdev: " + stdev + " cycles, variance: " + variance + " cycles";
}
"""

if __name__ == '__main__':
  main()

