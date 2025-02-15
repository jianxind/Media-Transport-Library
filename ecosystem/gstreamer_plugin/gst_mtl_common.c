/*
 * Copyright (C) 2024 Intel Corporation
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "gst_mtl_common.h"

guint gst_mtl_port_idx = MTL_PORT_P;

gboolean gst_mtl_common_parse_input_finfo(const GstVideoFormatInfo* finfo,
                                          enum st_frame_fmt* fmt) {
  if (finfo->format == GST_VIDEO_FORMAT_v210) {
    *fmt = ST_FRAME_FMT_V210;
  } else if (finfo->format == GST_VIDEO_FORMAT_I422_10LE) {
    *fmt = ST_FRAME_FMT_YUV422PLANAR10LE;
  } else {
    return FALSE;
  }

  return TRUE;
}

gboolean gst_mtl_common_parse_fps_code(gint fps_code, enum st_fps* fps) {
  if (!fps) {
    GST_ERROR("Invalid fps pointer");
    return FALSE;
  }

  switch (fps_code) {
    case GST_MTL_SUPPORTED_FPS_120:
      *fps = ST_FPS_P120;
      break;
    case GST_MTL_SUPPORTED_FPS_119_88:
      *fps = ST_FPS_P119_88;
      break;
    case GST_MTL_SUPPORTED_FPS_100:
      *fps = ST_FPS_P100;
      break;
    case GST_MTL_SUPPORTED_FPS_60:
      *fps = ST_FPS_P60;
      break;
    case GST_MTL_SUPPORTED_FPS_59_94:
      *fps = ST_FPS_P59_94;
      break;
    case GST_MTL_SUPPORTED_FPS_50:
      *fps = ST_FPS_P50;
      break;
    case GST_MTL_SUPPORTED_FPS_30:
      *fps = ST_FPS_P30;
      break;
    case GST_MTL_SUPPORTED_FPS_29_97:
      *fps = ST_FPS_P29_97;
      break;
    case GST_MTL_SUPPORTED_FPS_25:
      *fps = ST_FPS_P25;
      break;
    case GST_MTL_SUPPORTED_FPS_24:
      *fps = ST_FPS_P24;
      break;
    case GST_MTL_SUPPORTED_FPS_23_98:
      *fps = ST_FPS_P23_98;
      break;
    default:
      return FALSE;
  }

  return TRUE;
}

gboolean gst_mtl_common_parse_fps(GstVideoInfo* info, enum st_fps* fps) {
  gint fps_div;
  if (info->fps_n <= 0 || info->fps_d <= 0) {
    return FALSE;
  }

  fps_div = info->fps_n / info->fps_d;

  switch (fps_div) {
    case 24:
      *fps = ST_FPS_P24;
      break;
    case 25:
      *fps = ST_FPS_P25;
      break;
    case 30:
      *fps = ST_FPS_P30;
      break;
    case 50:
      *fps = ST_FPS_P50;
      break;
    case 60:
      *fps = ST_FPS_P60;
      break;
    case 120:
      *fps = ST_FPS_P120;
      break;
    default:
      return FALSE;
  }

  return TRUE;
}

/* includes all formats supported by the library for future support */
gboolean gst_mtl_common_parse_pixel_format(const char* format, enum st_frame_fmt* fmt) {
  if (!fmt || !format) {
    GST_ERROR("%s, invalid input\n", __func__);
    return FALSE;
  }

  if (strcmp(format, "YUV422PLANAR10LE") == 0) {
    *fmt = ST_FRAME_FMT_YUV422PLANAR10LE;
  } else if (strcmp(format, "v210") == 0) {
    *fmt = ST_FRAME_FMT_V210;
  } else if (strcmp(format, "Y210") == 0) {
    *fmt = ST_FRAME_FMT_Y210;
  } else if (strcmp(format, "YUV422PLANAR8") == 0) {
    *fmt = ST_FRAME_FMT_YUV422PLANAR8;
  } else if (strcmp(format, "UYVY") == 0) {
    *fmt = ST_FRAME_FMT_UYVY;
  } else if (strcmp(format, "YUV422RFC4175PG2BE10") == 0) {
    *fmt = ST_FRAME_FMT_YUV422RFC4175PG2BE10;
  } else if (strcmp(format, "YUV422PLANAR12LE") == 0) {
    *fmt = ST_FRAME_FMT_YUV422PLANAR12LE;
  } else if (strcmp(format, "YUV422RFC4175PG2BE12") == 0) {
    *fmt = ST_FRAME_FMT_YUV422RFC4175PG2BE12;
  } else if (strcmp(format, "YUV444PLANAR10LE") == 0) {
    *fmt = ST_FRAME_FMT_YUV444PLANAR10LE;
  } else if (strcmp(format, "YUV444RFC4175PG4BE10") == 0) {
    *fmt = ST_FRAME_FMT_YUV444RFC4175PG4BE10;
  } else if (strcmp(format, "YUV444PLANAR12LE") == 0) {
    *fmt = ST_FRAME_FMT_YUV444PLANAR12LE;
  } else if (strcmp(format, "YUV444RFC4175PG2BE12") == 0) {
    *fmt = ST_FRAME_FMT_YUV444RFC4175PG2BE12;
  } else if (strcmp(format, "YUV420CUSTOM8") == 0) {
    *fmt = ST_FRAME_FMT_YUV420CUSTOM8;
  } else if (strcmp(format, "YUV422CUSTOM8") == 0) {
    *fmt = ST_FRAME_FMT_YUV422CUSTOM8;
  } else if (strcmp(format, "YUV420PLANAR8") == 0) {
    *fmt = ST_FRAME_FMT_YUV420PLANAR8;
  } else if (strcmp(format, "ARGB") == 0) {
    *fmt = ST_FRAME_FMT_ARGB;
  } else if (strcmp(format, "BGRA") == 0) {
    *fmt = ST_FRAME_FMT_BGRA;
  } else if (strcmp(format, "RGB8") == 0) {
    *fmt = ST_FRAME_FMT_RGB8;
  } else if (strcmp(format, "GBRPLANAR10LE") == 0) {
    *fmt = ST_FRAME_FMT_GBRPLANAR10LE;
  } else if (strcmp(format, "RGBRFC4175PG4BE10") == 0) {
    *fmt = ST_FRAME_FMT_RGBRFC4175PG4BE10;
  } else if (strcmp(format, "GBRPLANAR12LE") == 0) {
    *fmt = ST_FRAME_FMT_GBRPLANAR12LE;
  } else if (strcmp(format, "RGBRFC4175PG2BE12") == 0) {
    *fmt = ST_FRAME_FMT_RGBRFC4175PG2BE12;
  } else {
    GST_ERROR("invalid output format %s\n", format);
    return FALSE;
  }

  return TRUE;
}

gboolean gst_mtl_common_parse_audio_format(const char* format, enum st30_fmt* audio) {
  if (!audio || !format) {
    GST_ERROR("%s, invalid input\n", __func__);
    return FALSE;
  }

  if (strcmp(format, "PCM8") == 0) {
    *audio = ST30_FMT_PCM8;
  } else if (strcmp(format, "PCM16") == 0) {
    *audio = ST30_FMT_PCM16;
  } else if (strcmp(format, "PCM24") == 0) {
    *audio = ST30_FMT_PCM24;
  } else if (strcmp(format, "AM824") == 0) {
    *audio = ST31_FMT_AM824;
  } else {
    GST_ERROR("%s, invalid audio format %s\n", __func__, format);
    return FALSE;
  }

  return TRUE;
}

gboolean gst_mtl_common_parse_sampling(gint sampling, enum st30_sampling* st_sampling) {
  if (!st_sampling) {
    GST_ERROR("Invalid st_sampling pointer");
    return FALSE;
  }

  switch (sampling) {
    case GST_MTL_SUPPORTED_AUDIO_SAMPLING_44_1K:
      *st_sampling = ST31_SAMPLING_44K;
      return TRUE;
    case GST_MTL_SUPPORTED_AUDIO_SAMPLING_48K:
      *st_sampling = ST30_SAMPLING_48K;
      return TRUE;
    case GST_MTL_SUPPORTED_AUDIO_SAMPLING_96K:
      *st_sampling = ST30_SAMPLING_96K;
      return TRUE;
    default:
      return FALSE;
  }
}

void gst_mtl_common_init_general_argumetns(GObjectClass* gobject_class) {
  g_object_class_install_property(
      gobject_class, PROP_GENERAL_LOG_LEVEL,
      g_param_spec_uint("log-level", "Log Level", "Set the log level (INFO 1 to CRIT 5).",
                        1, MTL_LOG_LEVEL_MAX, 1,
                        G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_GENERAL_DEV_ARGS_PORT,
      g_param_spec_string("dev-port", "DPDK device port",
                          "DPDK port for synchronous ST 2110 data"
                          "video transmission, bound to the VFIO DPDK driver. ",
                          NULL, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_GENERAL_DEV_ARGS_SIP,
      g_param_spec_string("dev-ip", "Local device IP",
                          "Local IP address that the port will be "
                          "identified by. This is the address from which ARP "
                          "responses will be sent.",
                          NULL, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_GENERAL_DEV_ARGS_DMA_DEV,
      g_param_spec_string("dma-dev", "DPDK DMA port",
                          "DPDK port for the MTL direct memory functionality.", NULL,
                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_GENERAL_PORT_PORT,
      g_param_spec_string("port", "Transmission Device Port",
                          "DPDK device port initialized for the transmission.", NULL,
                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_GENERAL_PORT_IP,
      g_param_spec_string("ip", "Sender node's IP", "Receiving MTL node IP address.",
                          NULL, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_GENERAL_PORT_UDP_PORT,
      g_param_spec_uint("udp-port", "Sender UDP port", "Receiving MTL node UDP port.", 0,
                        G_MAXUINT, 20000, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_GENERAL_PORT_TX_QUEUES,
      g_param_spec_uint("tx-queues", "Number of TX queues",
                        "Number of TX queues to initialize in DPDK backend.", 0,
                        G_MAXUINT, 16, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_GENERAL_PORT_RX_QUEUES,
      g_param_spec_uint("rx-queues", "Number of RX queues",
                        "Number of RX queues to initialize in DPDK backend.", 0,
                        G_MAXUINT, 16, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_GENERAL_PORT_PAYLOAD_TYPE,
      g_param_spec_uint("payload-type", "ST 2110 payload type",
                        "SMPTE ST 2110 payload type.", 0, G_MAXUINT, 112,
                        G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
}

void gst_mtl_common_set_general_argumetns(GObject* object, guint prop_id,
                                          const GValue* value, GParamSpec* pspec,
                                          StDevArgs* devArgs, SessionPortArgs* portArgs,
                                          guint* log_level) {
  switch (prop_id) {
    case PROP_GENERAL_LOG_LEVEL:
      *log_level = g_value_get_uint(value);
      break;
    case PROP_GENERAL_DEV_ARGS_PORT:
      strncpy(devArgs->port, g_value_get_string(value), MTL_PORT_MAX_LEN);
      break;
    case PROP_GENERAL_DEV_ARGS_SIP:
      strncpy(devArgs->local_ip_string, g_value_get_string(value), MTL_PORT_MAX_LEN);
      break;
    case PROP_GENERAL_DEV_ARGS_DMA_DEV:
      strncpy(devArgs->dma_dev, g_value_get_string(value), MTL_PORT_MAX_LEN);
      break;
    case PROP_GENERAL_PORT_PORT:
      strncpy(portArgs->port, g_value_get_string(value), MTL_PORT_MAX_LEN);
      break;
    case PROP_GENERAL_PORT_IP:
      strncpy(portArgs->session_ip_string, g_value_get_string(value), MTL_PORT_MAX_LEN);
      break;
    case PROP_GENERAL_PORT_UDP_PORT:
      portArgs->udp_port = g_value_get_uint(value);
      break;
    case PROP_GENERAL_PORT_PAYLOAD_TYPE:
      portArgs->payload_type = g_value_get_uint(value);
      break;
    case PROP_GENERAL_PORT_RX_QUEUES:
      devArgs->rx_queues_cnt[MTL_PORT_P] = g_value_get_uint(value);
      break;
    case PROP_GENERAL_PORT_TX_QUEUES:
      devArgs->tx_queues_cnt[MTL_PORT_P] = g_value_get_uint(value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

void gst_mtl_common_get_general_argumetns(GObject* object, guint prop_id,
                                          const GValue* value, GParamSpec* pspec,
                                          StDevArgs* devArgs, SessionPortArgs* portArgs,
                                          guint* log_level) {
  switch (prop_id) {
    case PROP_GENERAL_LOG_LEVEL:
      g_value_set_uint(value, *log_level);
      break;
    case PROP_GENERAL_DEV_ARGS_PORT:
      g_value_set_string(value, devArgs->port);
      break;
    case PROP_GENERAL_DEV_ARGS_SIP:
      g_value_set_string(value, devArgs->local_ip_string);
      break;
    case PROP_GENERAL_DEV_ARGS_DMA_DEV:
      g_value_set_string(value, devArgs->dma_dev);
      break;
    case PROP_GENERAL_PORT_PORT:
      g_value_set_string(value, portArgs->port);
      break;
    case PROP_GENERAL_PORT_IP:
      g_value_set_string(value, portArgs->session_ip_string);
      break;
    case PROP_GENERAL_PORT_UDP_PORT:
      g_value_set_uint(value, portArgs->udp_port);
      break;
    case PROP_GENERAL_PORT_PAYLOAD_TYPE:
      g_value_set_uint(value, portArgs->payload_type);
      break;
    case PROP_GENERAL_PORT_RX_QUEUES:
      g_value_set_uint(value, devArgs->rx_queues_cnt[MTL_PORT_P]);
      break;
    case PROP_GENERAL_PORT_TX_QUEUES:
      g_value_set_uint(value, devArgs->tx_queues_cnt[MTL_PORT_P]);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

gboolean gst_mtl_common_parse_dev_arguments(struct mtl_init_params* mtl_init_params,
                                            StDevArgs* devArgs) {
  gint ret;

  if (gst_mtl_port_idx > MTL_PORT_R) {
    GST_ERROR("%s, invalid port number %d\n", __func__, gst_mtl_port_idx);
    return FALSE;
  }

  strncpy(mtl_init_params->port[gst_mtl_port_idx], devArgs->port, MTL_PORT_MAX_LEN);

  ret = inet_pton(AF_INET, devArgs->local_ip_string,
                  mtl_init_params->sip_addr[gst_mtl_port_idx]);
  if (ret != 1) {
    GST_ERROR("%s, sip %s is not valid ip address\n", __func__, devArgs->local_ip_string);
    return FALSE;
  }

  if (devArgs->rx_queues_cnt[gst_mtl_port_idx]) {
    mtl_init_params->rx_queues_cnt[gst_mtl_port_idx] =
        devArgs->rx_queues_cnt[gst_mtl_port_idx];
  } else {
    mtl_init_params->rx_queues_cnt[gst_mtl_port_idx] = 16;
  }

  if (devArgs->tx_queues_cnt[gst_mtl_port_idx]) {
    mtl_init_params->tx_queues_cnt[gst_mtl_port_idx] =
        devArgs->tx_queues_cnt[gst_mtl_port_idx];
  } else {
    mtl_init_params->tx_queues_cnt[gst_mtl_port_idx] = 16;
  }

  mtl_init_params->num_ports++;

  if (devArgs->dma_dev && strlen(devArgs->dma_dev)) {
    strncpy(mtl_init_params->dma_dev_port[0], devArgs->dma_dev, MTL_PORT_MAX_LEN);
  }

  gst_mtl_port_idx++;
  return ret;
}

mtl_handle gst_mtl_common_init_handle(struct mtl_init_params* p, StDevArgs* devArgs,
                                      guint* log_level) {
  struct mtl_init_params mtl_init_params = {0};

  if (!p || !devArgs || !log_level) {
    GST_ERROR("Invalid input");
    return NULL;
  }

  mtl_init_params.num_ports = 0;

  if (gst_mtl_common_parse_dev_arguments(&mtl_init_params, devArgs) == FALSE) {
    GST_ERROR("Failed to parse dev arguments");
    return NULL;
  }
  mtl_init_params.flags |= MTL_FLAG_BIND_NUMA;

  /*
   * Log levels range from 1 to LOG_LEVEL_MAX.
   * We avoid using 0 (DEBUG) in normal scenarios,
   * so it's acceptable to use 0 as a placeholder.
   */
  if (*log_level && *log_level < MTL_LOG_LEVEL_MAX) {
    mtl_init_params.log_level = *log_level;
  } else {
    mtl_init_params.log_level = MTL_LOG_LEVEL_INFO;
  }
  *log_level = mtl_init_params.log_level;

  return mtl_init(&mtl_init_params);
}
