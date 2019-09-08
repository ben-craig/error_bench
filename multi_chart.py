#!/usr/bin/env python
import statistics
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
PIX_HEIGHT=30

CASE_ORDER = [
  "throw_exception",
  "throw_struct",
  "throw_val",
  "noexcept_terminate",
  "terminate",
  "noexcept_abort",
  "abort",
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
def case_sorter(case_name):
  return CASE_ORDER_DICT[case_name]

def parse_line(line, frames):
  [full_case, mood, frame_str, value_str] = line.split(',')
  value = float(value_str) * CPU_FREQ
  frame_thing = mood + "_" + frame_str
  pieces = full_case.split('\\')
  plat_name = pieces[0]
  case_name = pieces[2].rstrip('_')
  iter = int(pieces[3])

  platforms = frames.setdefault(frame_thing, {})
  cases = platforms.setdefault(plat_name, {})
  values = {}
  if case_name not in cases:
    cases[case_name] = values
  else:
    values = cases[case_name]
  values[iter] = value

def bucket_data(hist, value, width):
  bucket = round(value/width, 0) * width
  count = hist.setdefault(bucket, 0)
  hist[bucket] = count+1
  return bucket

def parse_file(file_name, platforms):
  with open(file_name, 'r') as fin:
    for line in fin:
      parse_line(line, platforms)

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

MAX_DESIRED_BUCKETS = 300.0
def calc_width(min_x, max_x):
  start_width = float(max_x - min_x) / MAX_DESIRED_BUCKETS
  return aesthetic_round(start_width)

def calc_stats(values):
  mean = statistics.mean(values)
  median = statistics.median(values)
  stdev = statistics.stdev(values, mean)
  variance = statistics.variance(values, mean)
  return {"mean" : mean, "median" : median, "stdev": stdev, "variance": variance}

def emit_stats(fout, stats):
  fout.write("var means = {\n")
  for name, stat_struct in sorted(stats.items()):
    data_str = "{:.2f}".format(stat_struct["mean"])
    fout.write("  '" + name + "': " + data_str + ",\n")
  fout.write("};\n")

  fout.write("var medians = {\n")
  for name, stat_struct in sorted(stats.items()):
    data_str = "{:.2f}".format(stat_struct["median"])
    fout.write("  '" + name + "': " + data_str + ",\n")
  fout.write("};\n")

  fout.write("var stdevs = {\n")
  for name, stat_struct in sorted(stats.items()):
    data_str = "{:.2f}".format(stat_struct["stdev"])
    fout.write("  '" + name + "': " + data_str + ",\n")
  fout.write("};\n")

  fout.write("var variances = {\n")
  for name, stat_struct in sorted(stats.items()):
    data_str = "{:.2f}".format(stat_struct["variance"])
    fout.write("  '" + name + "': " + data_str + ",\n")
  fout.write("};\n")

def emit_data(fout, noexcept, sad, platforms):
  min_x = 10000000.0
  max_x = 0.0
  stats = {}
  for plat_name, cases in sorted(platforms.items()):
    for case_name in sorted(cases.keys(), key=case_sorter):
      if noexcept and "throw_" in case_name:
        continue
      if sad and "terminate" in case_name:
        continue
      values = cases[case_name].values()
      for value in values:
        min_x = min(min_x, value)
        max_x = max(max_x, value)
      stats[plat_name + "." + case_name] = calc_stats(values)
  emit_stats(fout, stats)

  width = calc_width(min_x, max_x)

  min_x = 10000000.0
  max_x = 0.0

  fout.write("var theData = {\n")
  for plat_name, cases in sorted(platforms.items()):
    fout.write("  " + plat_name + ": {\n")
    for case_name in sorted(cases.keys(), key=case_sorter):
      if noexcept and "throw_" in case_name:
        continue
      if sad and "terminate" in case_name:
        continue
      fout.write("    " + case_name + ": [\n")
      hist = {}
      for value in cases[case_name].values():
        bucketed = bucket_data(hist, value, width)
        min_x = min(min_x, bucketed)
        max_x = max(max_x, bucketed)
      for val, count in sorted(hist.items()):
        fout.write("      [" + str(val) + ", " + str(count) + "],\n")
      fout.write("    ],\n")
    fout.write("  },\n")
  fout.write("};\n")
  fout.write("var minXValue = " + str(min_x - 2 * width) + ";\n")
  fout.write("var maxXValue = " + str(max_x + 2 * width) + ";\n")

def emit_grids(fout, num_charts):
  fout.write("var theGrids = [\n")
  top = START_PIX
  for i in range(num_charts):
    mid = top + PIX_HEIGHT
    fout.write("  Object.assign({top: " + str(top) + "}, commonGrid),\n")
    fout.write("  Object.assign({top: " + str(mid) + "}, commonGrid),\n")
    top = mid + PIX_HEIGHT
  fout.write("];\n")
  fout.write("var gridHeightNeeded = " + str(top) + ";\n")

def emit_xAxis(fout, num_charts, noexcept, sad, platforms):
  fout.write("var theXAxes = [\n")
  idx = 0
  for plat_name, cases in sorted(platforms.items()):
    for case_name in sorted(cases.keys(), key=case_sorter):
      if noexcept and "throw_" in case_name:
        continue
      if sad and "terminate" in case_name:
        continue
      name = plat_name + "." + case_name
      fout.write("  make_xAxis('" + name + "', " + str(2*idx) + ", false, minXValue, maxXValue),\n")
      showAxis = "false"
      if idx == num_charts-1:
        showAxis = "true"
      fout.write("  make_xAxis('" + name + "', " + str(2*idx+1) + ", " + showAxis + ", minXValue, maxXValue),\n")
      idx = idx + 1
  fout.write("];\n")
  fout.write("var xAxisIndices = [\n  ")
  for i in range(2*num_charts):
    fout.write(str(i) + ", ")
  fout.write("\n]\n")

def emit_yAxis(fout, num_charts):
  fout.write("var theYAxes = [\n")
  for i in range(num_charts):
    fout.write("  Object.assign({gridIndex: " + str(2*i) + "}, commonYAxis),\n")
    fout.write("  Object.assign({gridIndex: " + str(2*i+1) + "}, invertYAxis),\n")
  fout.write("];\n")

def emit_single_series(fout, plat_name, case_name, idx):
  name = plat_name + "." + case_name
  dataStr = "theData." + name
  color = COLORS[idx % len(COLORS)]
  fout.write("  make_series( '" +name + "', " + str(2*idx) + ", " + dataStr + ", '#" + color + "'),\n")
  fout.write("  make_series( '" +name + "', " + str(2*idx+1) + ", " + dataStr + ", '#" + color + "'),\n")

def emit_series(fout, noexcept, sad, platforms):
  fout.write("var theSeries = [\n")
  idx = 0
  for plat_name, cases in sorted(platforms.items()):
    for case_name in sorted(cases.keys(), key=case_sorter):
      if noexcept and "throw_" in case_name:
        continue
      if sad and "terminate" in case_name:
        continue
      emit_single_series(fout, plat_name, case_name, idx)
      idx = idx + 1
  fout.write("];\n")

def emit_barSeries(fout, noexcept, sad, platforms):
  fout.write("var barSeries = [\n")
  idx = 0
  for case_name in sorted(platforms["MSVC_x64"].keys(), key=case_sorter):
    if noexcept and "throw_" in case_name:
      continue
    if sad and "terminate" in case_name:
      continue
    color = COLORS[idx % len(COLORS)]
    fout.write("  {\n")
    fout.write("    type: 'bar',\n")
    fout.write("    name: '" + case_name + "',\n")
    fout.write("    itemStyle: {color: '#" + color + "'},\n")
    fout.write("    data: [\n")
    for plat_name in sorted(platforms.keys()):
      fout.write("      medians['" + plat_name + "." + case_name + "'],\n")
    fout.write("    ]\n")
    fout.write("  },\n")
    idx = idx + 1
  fout.write("];\n")

def emit_barYAxisData(fout, platforms):
  fout.write("var barYAxisData = [\n")
  for plat_name in sorted(platforms.keys()):
    fout.write("  '" + plat_name + "',\n")
  fout.write("];\n")

def emit_big_js(file_name, platforms):
  num_charts = 0
  num_noexcept_charts = 0
  sad = ("sad" in file_name)
  for cases in platforms.values():
    for case_name in cases.keys():
      if sad and "terminate" in case_name:
        continue
      num_charts = num_charts + 1
      if "throw_" in case_name:
        continue
      num_noexcept_charts = num_noexcept_charts + 1
  with open(file_name, 'w') as fout:
    fout.write(HTML_HEADER)
    emit_boilerplate(fout)
    emit_data(fout, False, sad, platforms)
    emit_grids(fout, num_charts)
    emit_xAxis(fout, num_charts, False, sad, platforms)
    emit_yAxis(fout, num_charts)
    emit_series(fout, False, sad, platforms)
    emit_barSeries(fout, False, sad, platforms)
    emit_barYAxisData(fout, platforms)
    fout.write(HTML_FOOTER)
  with open("noexcept_" + file_name, 'w') as fout:
    fout.write(HTML_HEADER)
    emit_boilerplate(fout)
    emit_data(fout, True, sad, platforms)
    emit_grids(fout, num_noexcept_charts)
    emit_xAxis(fout, num_noexcept_charts, True, sad, platforms)
    emit_yAxis(fout, num_noexcept_charts)
    emit_series(fout, True, sad, platforms)
    emit_barSeries(fout, True, sad, platforms)
    emit_barYAxisData(fout, platforms)
    fout.write(HTML_FOOTER)

def main():
  frames = {}
  parse_file("gauss_times.csv", frames)
  for frame, platforms in frames.items():
    emit_big_js(frame + ".html", platforms)

HTML_HEADER = """
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <script src="echarts_modified.js"></script>
    <script type="text/javascript">

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
"""
HTML_FOOTER = """
    </script>
</head>
<body>
    <!-- prepare a DOM container with width and height -->
    <div id="Violin" style="width: 100%;height:10px;"></div>
    <div id="Bar" style="width: 100%;height:10px;"></div>
    <script type="text/javascript">
// based on prepared DOM, initialize echarts instance
document.getElementById('Violin').setAttribute("style","height:"+(gridHeightNeeded + 60) + "px");
var myChart = echarts.init(document.getElementById('Violin'));
document.getElementById('Bar').setAttribute("style","height:"+(300) + "px");
var barChart = echarts.init(document.getElementById('Bar'));

function myFormatter(params, ticket, callback) {
  mean = means[params.seriesName];
  median = medians[params.seriesName];
  stdev = stdevs[params.seriesName];
  variance = variances[params.seriesName];
  return params.seriesName + "<br />" +
    params.value[0] + " cycles, " + params.value[1] + " samples" + "<br />" +
    "median: " + median + " cycles, mean: " + mean + " cycles"  + "<br />" +
    "stdev: " + stdev + " cycles, variance: " + variance + " cycles";
}

option = {
  tooltip : {
    formatter: myFormatter,
  },
  dataZoom: [
    {
      show: true,
      startValue: minXValue,
      endValue: maxXValue,
      xAxisIndex: xAxisIndices,
    },
  ],
  grid: theGrids,
  xAxis: theXAxes,
  yAxis: theYAxes,
  series: theSeries,
};

myChart.setOption(option);

var barOption = {
  tooltip: { },
  calculable : true,
  legend: {
    right: 0,
    top: 0,
    orient: 'vertical',
  },
  yAxis: [{
    type: 'category',
    inverse:true,
    data: barYAxisData
  }],
  xAxis: [{
    type: 'value'
  }],
  grid: {
    top: 0,
    left: 130,
  },
  series: barSeries
};

barChart.setOption(barOption);

</script>

</body>
</html>
"""

if __name__ == '__main__':
  main()

