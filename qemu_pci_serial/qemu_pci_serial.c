#include <linux/device.h>
#include <linux/module.h>
#include <linux/8250_pci.h>
#include <linux/pci.h>
#include <linux/serial_core.h>
#include <linux/serial_8250.h>

static struct pciserial_board pci_boards[] = {
	[0] = {
		.flags		= FL_BASE0,
		.num_ports	= 1,
		.base_baud	= 115200,
		.uart_offset	= 8,
	},
};

static int qemu_pci_serial_init(void)
{
	struct pci_dev *dev = pci_get_device(0x1b36, 0x0002, NULL);
	struct pciserial_board *board = &pci_boards[0];
	struct serial_private *priv;
	int rc;

	rc = pcim_enable_device(dev);
	pci_save_state(dev);
	if (rc)
		return rc;

	priv = pciserial_init_ports(dev, board);
	if (IS_ERR(priv))
		return PTR_ERR(priv);

	pci_set_drvdata(dev, priv);

	return 0;
}

static void qemu_pci_serial_exit(void)
{
	struct pci_dev *dev = pci_get_device(0x1b36, 0x0002, NULL);
	struct serial_private *priv = pci_get_drvdata(dev);

	pciserial_remove_ports(priv);
}

module_init(qemu_pci_serial_init);
module_exit(qemu_pci_serial_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("QEMU pci serial device driver");