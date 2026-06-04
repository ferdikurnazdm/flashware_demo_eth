/* generated common source file - do not edit */
#include "common_data.h"

const ether_phy_lsi_cfg_t g_ether_phy_lsi0 =
{ .address = 0, .type = ETHER_PHY_LSI_TYPE_KIT_COMPONENT, };
ether_phy_instance_ctrl_t g_ether_phy0_ctrl;
#define RA_NOT_DEFINED (1)
const ether_phy_extended_cfg_t g_ether_phy0_extended_cfg =
{ .p_target_init = NULL, .p_target_link_partner_ability_get = NULL, .p_phy_lsi_cfg_list =
{
#if (RA_NOT_DEFINED != g_ether_phy_lsi0)
  &g_ether_phy_lsi0,
#else
    	NULL,
#endif
          }, };
#undef RA_NOT_DEFINED
const ether_phy_cfg_t g_ether_phy0_cfg =
{

.channel = 0,
  .phy_lsi_address = 0, .phy_reset_wait_time = 0x00020000, .mii_bit_access_wait_time = 8, .phy_lsi_type =
          ETHER_PHY_LSI_TYPE_KIT_COMPONENT,
  .flow_control = ETHER_PHY_FLOW_CONTROL_DISABLE, .mii_type = ETHER_PHY_MII_TYPE_RMII, .p_context = NULL, .p_extend =
          &g_ether_phy0_extended_cfg,

};
/* Instance structure to use this module. */
const ether_phy_instance_t g_ether_phy0 =
{ .p_ctrl = &g_ether_phy0_ctrl, .p_cfg = &g_ether_phy0_cfg, .p_api = &g_ether_phy_on_ether_phy };
ether_instance_ctrl_t g_ether0_ctrl;

uint8_t g_ether0_mac_address[6] =
{ 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };

__attribute__((__aligned__(16))) ether_instance_descriptor_t g_ether0_tx_descriptors[1] ETHER_BUFFER_PLACE_IN_SECTION;
__attribute__((__aligned__(16))) ether_instance_descriptor_t g_ether0_rx_descriptors[1] ETHER_BUFFER_PLACE_IN_SECTION;

__attribute__((__aligned__(32)))uint8_t g_ether0_ether_buffer0[1536]ETHER_BUFFER_PLACE_IN_SECTION;
__attribute__((__aligned__(32)))uint8_t g_ether0_ether_buffer1[1536]ETHER_BUFFER_PLACE_IN_SECTION;

uint8_t *pp_g_ether0_ether_buffers[2] =
{ (uint8_t*) &g_ether0_ether_buffer0[0], (uint8_t*) &g_ether0_ether_buffer1[0], };

const ether_extended_cfg_t g_ether0_extended_cfg_t =
{ .p_rx_descriptors = g_ether0_rx_descriptors, .p_tx_descriptors = g_ether0_tx_descriptors, .eesr_event_filter =
          (ETHER_EESR_EVENT_MASK_RFOF | ETHER_EESR_EVENT_MASK_RDE | ETHER_EESR_EVENT_MASK_FR
                  | ETHER_EESR_EVENT_MASK_TFUF | ETHER_EESR_EVENT_MASK_TDE | ETHER_EESR_EVENT_MASK_TC | 0U),
  .ecsr_event_filter = (0U), };

const ether_cfg_t g_ether0_cfg =
{ .channel = 0, .zerocopy = ETHER_ZEROCOPY_DISABLE, .multicast = ETHER_MULTICAST_ENABLE, .promiscuous =
          ETHER_PROMISCUOUS_DISABLE,
  .flow_control = ETHER_FLOW_CONTROL_DISABLE, .padding = ETHER_PADDING_DISABLE, .padding_offset = 0, .broadcast_filter =
          0,
  .p_mac_address = g_ether0_mac_address,

  .num_tx_descriptors = 1,
  .num_rx_descriptors = 1,

  .pp_ether_buffers = pp_g_ether0_ether_buffers,

  .ether_buffer_size = 1536,

#if defined(VECTOR_NUMBER_EDMAC0_EINT)
                .irq                = VECTOR_NUMBER_EDMAC0_EINT,
#else
  .irq = FSP_INVALID_VECTOR,
#endif

  .interrupt_priority = (12),

  .p_callback = vEtherISRCallback,
  .p_ether_phy_instance = &g_ether_phy0, .p_context = &g_freertos_plus_tcp0, .p_extend = &g_ether0_extended_cfg_t, };

/* Instance structure to use this module. */
const ether_instance_t g_ether0 =
{ .p_ctrl = &g_ether0_ctrl, .p_cfg = &g_ether0_cfg, .p_api = &g_ether_on_ether };
#if (ipconfigIPv4_BACKWARD_COMPATIBLE == 0)
NetworkInterface_t g_freertos_plus_tcp0_xInterface =
{ .pvArgument = (void*) &g_freertos_plus_tcp0 };
#else
 rm_freertos_plus_tcp_instance_t * gp_freertos_plus_tcp_instance = &g_freertos_plus_tcp0;
#endif

static rm_freertos_plus_tcp_ctrl_t g_freertos_plus_tcp0_ctrl;

static rm_freertos_plus_tcp_cfg_t g_freertos_plus_tcp0_cfg =
{ .p_ether_instance = (ether_instance_t*) (&g_ether0),
  .rx_handler_task_stacksize = configMINIMAL_STACK_SIZE,
  .rx_handler_task_priority = configMAX_PRIORITIES - 1,
  .check_link_status_task_stacksize = configMINIMAL_STACK_SIZE,
  .check_link_status_task_priority = configMAX_PRIORITIES - 1,
  .link_check_interval = 1000, };

rm_freertos_plus_tcp_instance_t g_freertos_plus_tcp0 =
{ .p_ctrl = &g_freertos_plus_tcp0_ctrl, .p_cfg = &g_freertos_plus_tcp0_cfg };
ioport_instance_ctrl_t g_ioport_ctrl;
const ioport_instance_t g_ioport =
{ .p_api = &g_ioport_on_ioport, .p_ctrl = &g_ioport_ctrl, .p_cfg = &g_bsp_pin_cfg, };
QueueHandle_t g_input_queue;
#if 1
StaticQueue_t g_input_queue_memory;
uint8_t g_input_queue_queue_memory[4 * 256];
#endif
void rtos_startup_err_callback(void *p_instance, void *p_data);
QueueHandle_t g_output_queue;
#if 1
StaticQueue_t g_output_queue_memory;
uint8_t g_output_queue_queue_memory[256 * 4];
#endif
void rtos_startup_err_callback(void *p_instance, void *p_data);
void g_common_init(void)
{
    g_input_queue =
#if 1
            xQueueCreateStatic (
#else
                xQueueCreate(
                #endif
                                256,
                                4
#if 1
                                ,
                                &g_input_queue_queue_memory[0], &g_input_queue_memory
#endif
                                );
    if (NULL == g_input_queue)
    {
        rtos_startup_err_callback (g_input_queue, 0);
    }
    g_output_queue =
#if 1
            xQueueCreateStatic (
#else
                xQueueCreate(
                #endif
                                4,
                                256
#if 1
                                ,
                                &g_output_queue_queue_memory[0], &g_output_queue_memory
#endif
                                );
    if (NULL == g_output_queue)
    {
        rtos_startup_err_callback (g_output_queue, 0);
    }
}
