#include <stdio.h>
#include <cstddef>
#include <utility>
#include <math.h>
#include <algorithm>
#include <bits/stdc++.h>

template <class KeyClass,class ValueClass>
class BinaryTree
{
protected:
	class Node
	{
	public:
		KeyClass key;
		ValueClass value;
		Node *left,*right,*up;
		int height;
		Node() : left(nullptr),right(nullptr),up(nullptr),height(1)
		{
		}
	};
public:
	class NodeHandle
	{
	friend BinaryTree <KeyClass,ValueClass>;
	private:
		Node *ptr;
	public:
		inline void Nullify(void)
		{
			ptr=nullptr;
		}
		inline bool IsNull(void) const
		{
			return ptr==nullptr;
		}
		inline bool IsNotNull(void) const
		{
			return ptr!=nullptr;
		}
		inline bool operator==(NodeHandle hd) const
		{
			return this->ptr==hd.ptr;
		}
		inline bool operator!=(NodeHandle hd) const
		{
			return this->ptr!=hd.ptr;
		}
		inline bool operator==(std::nullptr_t) const
		{
			return ptr==nullptr;
		}
		inline bool operator!=(std::nullptr_t) const
		{
			return ptr!=nullptr;
		}
	};
protected:
	// void CheckBalance(Node *root, std::pair<int, int> &limitation, int depth)
	// {
	// 	if(!root)
	// 	{
	// 		limitation.first = std::min(limitation.first, depth);
	// 		limitation.second = std::max(limitation.second, depth);
	// 		return;
	// 	}
	// 	CheckBalance(root->left, limitation, depth+1);
	// 	CheckBalance(root->right, limitation, depth+1);
	// 	return;
	// }

	// void MakeBalance(Node *root)
	// {
	// 	Node *preRoot = new Node();
	// 	preRoot->right = root;
	// 	NodeHandle tmpNode;
	// 	tmpNode.ptr = preRoot;
	// 	int size = GetN(tmpNode);
	// 	TreeToVine(tmpNode);
	// 	VineToTree(tmpNode, size);
	// 	root = preRoot->right;
	// 	delete preRoot;
	// 	return;
	// }

	// void Rebalance(Node *fakeroot)
	// {
	// 	if(!root) return;
	// 	std::pair<int, int> limitation;
	// 	limitation.first = INT_MAX;
	// 	limitation.second = INT_MIN;
	// 	int depth = 0;
	// 	CheckBalance(root->left, limitation, depth+1);
	// 	CheckBalance(root->right, limitation,depth+1);
	// 	autoRebalance = limitation.second - limitation.first > 1;
	// 	printf("%i\n", limitation.first);
	// 	printf("%i\n", limitation.second);
	// 	if(!autoRebalance) return; // already balanced
	// 	else
	// 	{
	// 		MakeBalance(root);
	// 	}
	// }


	bool CheckBalance(Node *root)
	{
		if(!root) return true;
		NodeHandle handlel, handler;
		handlel.ptr = root->left;
		handler.ptr = root->right;
		int hl = GetHeight(handlel);
		int hr = GetHeight(handler);
		return !((hl - hr < 2) && (hl - hr > -2));
	}

	void ReBalanced(Node *root)
	{
		if(!root) return;
		autoRebalance = CheckBalance(root);
		if(!autoRebalance) return;
		else
		{
			MakeBalance(root);
		}
	}

	void MakeBalance(Node *root)
	{
		Node *tmpPtr = new Node();
		tmpPtr->right = root;
		int size = GetN_node(root);
		NodeHandle handle;
		handle.ptr = tmpPtr;
		TreeToVine(handle);
		VineToTree(handle, size);
		root = tmpPtr->right;
		// UpdateHeight(root);
		// UpdateHeightCascade(root->right);
		delete tmpPtr;
		return;
	}

	Node *GetNode(NodeHandle ndHd)
	{
		if(ndHd.IsNotNull())
		{
			return ndHd.ptr;
		}
		return nullptr;
	}
	const Node *GetNode(NodeHandle ndHd) const
	{
		if(ndHd.IsNotNull())
		{
			return ndHd.ptr;
		}
		return nullptr;
	}
	static NodeHandle MakeHandle(Node *nodePtr)
	{
		NodeHandle ndHd;
		ndHd.ptr=nodePtr;
		return ndHd;
	}
	bool UpdateHeight(Node *nodePtr)
	{
		int leftHeight=1,rightHeight=1;
		if(nullptr!=nodePtr->left)
		{
			leftHeight=nodePtr->left->height+1;
		}
		if(nullptr!=nodePtr->right)
		{
			rightHeight=nodePtr->right->height+1;
		}
		int newHeight=1;
		if(leftHeight>rightHeight)
		{
			newHeight=leftHeight;
		}
		else
		{
			newHeight=rightHeight;
		}
		if(newHeight!=nodePtr->height)
		{
			nodePtr->height=newHeight;
			return true;
		}
		return false;
	}
	void UpdateHeightCascade(Node *nodePtr)
	{
		bool first=true;
		while(nullptr!=nodePtr)
		{
			auto changed=UpdateHeight(nodePtr);
			if(true!=first && true!=changed)
			{
				break;
			}
			nodePtr=nodePtr->up;
			first=false;
		}
	}

private:
	Node *root;
	long long int nElem;

public:
	bool autoRebalance;
	BinaryTree()
	{
		root=nullptr;
		nElem=0;
		autoRebalance=false;
	}
	~BinaryTree()
	{
		CleanUp();
	}
	void CleanUp(void)
	{
		CleanUp(GetNode(RootNode()));
	}
private:
	void CleanUp(Node *nodePtr)
	{
		if(nullptr!=nodePtr)
		{
			CleanUp(nodePtr->left);
			CleanUp(nodePtr->right);
			delete nodePtr;
		}
	}
public:
	static NodeHandle Null(void)
	{
		NodeHandle ndHd;
		ndHd.ptr=nullptr;
		return ndHd;
	}
	NodeHandle RootNode(void) const
	{
		return MakeHandle(root);
	}
	NodeHandle Left(NodeHandle ndHd) const
	{
		auto nodePtr=GetNode(ndHd);
		if(nullptr!=nodePtr)
		{
			return MakeHandle(nodePtr->left);
		}
		return Null();
	}
	NodeHandle Up(NodeHandle ndHd) const
	{
		auto nodePtr=GetNode(ndHd);
		if(nullptr!=nodePtr)
		{
			return MakeHandle(nodePtr->up);
		}
		return Null();
	}
	NodeHandle Right(NodeHandle ndHd) const
	{
		auto nodePtr=GetNode(ndHd);
		if(nullptr!=nodePtr)
		{
			return MakeHandle(nodePtr->right);
		}
		return Null();
	}

	long long int GetN(void) const
	{
		return nElem;
	}

	long long int GetN(NodeHandle ndHd) const
	{
		auto nodePtr = ndHd.ptr->right;
		return GetN_node(nodePtr);
	}

	long long int GetN_node(Node *root) const
	{
		if(!root) return 0;
		return GetN_node(root->left) + GetN_node(root->right) + 1;
	}

	const KeyClass &GetKey(NodeHandle ndHd) const
	{
		// This will crash if ndHd==nullptr.  Therefore, ndHd must be non-null to use this function.
		return GetNode(ndHd)->key;
	}
	ValueClass &GetValue(NodeHandle ndHd)
	{
		// This will crash if ndHd==nullptr.  Therefore, ndHd must be non-null to use this function.
		return GetNode(ndHd)->value;
	}
	const ValueClass &GetValue(NodeHandle ndHd) const
	{
		// This will crash if ndHd==nullptr.  Therefore, ndHd must be non-null to use this function.
		return GetNode(ndHd)->value;
	}
	NodeHandle FindNode(const KeyClass &key) const
	{
		auto ndHd=RootNode();
		while(nullptr!=ndHd)
		{
			if(key==GetKey(ndHd))
			{
				return ndHd;
			}
			if(key<GetKey(ndHd))
			{
				ndHd=Left(ndHd);
			}
			else
			{
				ndHd=Right(ndHd);
			}
		}
		return Null();
	}
	bool IsKeyIncluded(const KeyClass &key) const
	{
		return FindNode(key).IsNotNull();
	}
	int GetHeight(NodeHandle ndHd) const
	{
		auto nodePtr=GetNode(ndHd);
		if(nullptr!=nodePtr)
		{
			return nodePtr->height;
		}
		return 0;
	}

	NodeHandle Insert(const KeyClass &key,const ValueClass &value)
	{
		auto newNode=new Node;
		newNode->key=key;
		newNode->value=value;

		auto ndHd=RootNode();
		if(ndHd.IsNull())
		{
			root=newNode;
		}
		else
		{
			while(ndHd.IsNotNull())
			{
				if(key<GetKey(ndHd))
				{
					if(Left(ndHd)!=nullptr)
					{
						ndHd=Left(ndHd);
					}
					else
					{
						GetNode(ndHd)->left=newNode;
						newNode->up=GetNode(ndHd);
						break;
					}
				}
				else
				{
					if(Right(ndHd)!=nullptr)
					{
						ndHd=Right(ndHd);
					}
					else
					{
						GetNode(ndHd)->right=newNode;
						newNode->up=GetNode(ndHd);
						break;
					}
				}
			}
		}
		UpdateHeightCascade(newNode);
		nElem++;
		// Node *tmp_tail = newNode;
		// while(tmp_tail != root)
		// {
		// 	ReBalanced(tmp_tail);
		// 	tmp_tail = tmp_tail->up;
		// }
		// return MakeHandle(newNode);
	}

	NodeHandle First(void) const
	{
		auto ndHd=RootNode();
		while(Left(ndHd).IsNotNull())
		{
			ndHd=Left(ndHd);
		}
		return ndHd;
	}
	NodeHandle FindNext(NodeHandle ndHd) const
	{
		auto rightHd=Right(ndHd);
		if(rightHd.IsNotNull())
		{
			// Has a right sub-tree.
			// The next node is the left-most of the right sub-tree.
			ndHd=Right(ndHd);
			while(Left(ndHd).IsNotNull())
			{
				ndHd=Left(ndHd);
			}
			return ndHd;
		}
		else
		{
			// Does not have a right sub-tree.
			// Go up until it goes up from the left.
			while(ndHd.IsNotNull())
			{
				auto upHd=Up(ndHd);
				if(upHd.IsNotNull() && ndHd==Left(upHd))
				{
					return upHd;
				}
				ndHd=upHd;
			}
			return Null();
		}
	}
	NodeHandle Last(void) const;  // Do it in the assignment.
	NodeHandle FindPrev(NodeHandle ndHd) const;  // Do it in the assignment.



private:
	NodeHandle RightMostOf(NodeHandle ndHd)
	{
		while(Right(ndHd).IsNotNull())
		{
			ndHd=Right(ndHd);
		}
		return ndHd;
	}
	bool SimpleDetach(NodeHandle ndHd)
	{
		if(ndHd.IsNotNull())
		{
			auto upHd=Up(ndHd);
			auto rightHd=Right(ndHd);
			auto leftHd=Left(ndHd);
			if(rightHd.IsNull() && leftHd.IsNull())
			{
				if(upHd.IsNull()) // ndHd is a root.
				{
					root=nullptr;
				}
				else
				{
					auto upPtr=GetNode(upHd);
					if(Left(upHd)==ndHd)
					{
						upPtr->left=nullptr;
					}
					else if(Right(upHd)==ndHd)
					{
						upPtr->right=nullptr;
					}
					else
					{
						fprintf(stderr,"Error! Internal Tree Data Structure is broken.\n");
						return false;
					}
				}
				UpdateHeightCascade(GetNode(upHd));
				return true;
			}
			else if(rightHd.IsNull())
			{
				if(upHd.IsNull())
				{
					root=GetNode(leftHd);
					root->up=nullptr;
					return true;
				}
				else
				{
					// Connect upHd and leftHd
					auto upPtr=GetNode(upHd);
					auto leftPtr=GetNode(leftHd);
					if(Left(upHd)==ndHd)
					{
						upPtr->left=leftPtr;
						leftPtr->up=upPtr;
						UpdateHeightCascade(GetNode(upHd));
						return true;
					}
					else if(Right(upHd)==ndHd)
					{
						upPtr->right=leftPtr;
						leftPtr->up=upPtr;
						UpdateHeightCascade(GetNode(upHd));
						return true;
					}
					else
					{
						fprintf(stderr,"Error! Internal Tree Data Structure is broken.\n");
						return false;
					}
				}
			}
			else if(leftHd.IsNull())
			{
				if(upHd.IsNull())
				{
					root=GetNode(rightHd);
					root->up=nullptr;
					return true;
				}
				else
				{
					// Connect upHd and rightHd
					auto upPtr=GetNode(upHd);
					auto rightPtr=GetNode(rightHd);
					if(Left(upHd)==ndHd)
					{
						upPtr->left=rightPtr;
						rightPtr->up=upPtr;
						UpdateHeightCascade(GetNode(upHd));
						return true;
					}
					else if(Right(upHd)==ndHd)
					{
						upPtr->right=rightPtr;
						rightPtr->up=upPtr;
						UpdateHeightCascade(GetNode(upHd));
						return true;
					}
					else
					{
						fprintf(stderr,"Error! Internal Tree Data Structure is broken.\n");
						return false;
					}
				}
			}
			else
			{
				return false;
			}
		}
		return false;
	}
public:
	bool Delete(NodeHandle ndHd)
	{
		if(true==SimpleDetach(ndHd))
		{
			delete GetNode(ndHd);
			--nElem;
			return true;
		}
		else if(ndHd.IsNotNull())
		{
			// Right most of left. Always Simple-Detachable.
			// Also, since SimpleDetach of itself has failed, it must have a left sub-tree.
			auto RMOL=RightMostOf(Left(ndHd));
			if(true==SimpleDetach(RMOL))
			{
				// Now, RMOL needs to take position of ndHd.
				auto RMOLptr=GetNode(RMOL);
				auto upPtr=GetNode(Up(ndHd));
				auto leftPtr=GetNode(Left(ndHd));
				auto rightPtr=GetNode(Right(ndHd));

				auto upOfRMOLptr=RMOLptr->up;
				if(upOfRMOLptr==GetNode(ndHd))
				{
					upOfRMOLptr=RMOLptr;	// Now it is correct.
				}

				if(nullptr==upPtr)
				{
					root=RMOLptr;
					root->up=nullptr;
				}
				else if(upPtr->left==GetNode(ndHd))
				{
					upPtr->left=RMOLptr;
					RMOLptr->up=upPtr;
				}
				else if(upPtr->right==GetNode(ndHd))
				{
					upPtr->right=RMOLptr;
					RMOLptr->up=upPtr;
				}
				else
				{
					fprintf(stderr,"Error! Internal Tree Data Structure is broken.\n");
					return false;
				}

				RMOLptr->left=leftPtr;
				if(nullptr!=leftPtr)
				{
					leftPtr->up=RMOLptr;
				}
				RMOLptr->right=rightPtr;
				if(nullptr!=rightPtr)
				{
					rightPtr->up=RMOLptr;
				}

				UpdateHeightCascade(RMOLptr);

				delete GetNode(ndHd);
				--nElem;
				return true;
			}
		}
		return false; // Cannot delete a null node.
	}

	bool RotateLeft(NodeHandle ndHd)
	{
		auto nodePtr=GetNode(ndHd);
		if(nullptr!=nodePtr && nullptr!=nodePtr->right)
		{
			auto rightPtr=nodePtr->right;
			auto leftOfRight=nodePtr->right->left;

			if(nullptr==nodePtr->up)
			{
				root=rightPtr;
				rightPtr->up=nullptr;
			}
			else
			{
				rightPtr->up=nodePtr->up;
				if(nodePtr->up->left==nodePtr)
				{
					nodePtr->up->left=rightPtr;
				}
				else
				{
					nodePtr->up->right=rightPtr;
				}
			}

			rightPtr->left=nodePtr;
			nodePtr->up=rightPtr;

			nodePtr->right=leftOfRight;
			if(nullptr!=leftOfRight)
			{
				leftOfRight->up=nodePtr;
			}
			UpdateHeight(nodePtr);
			UpdateHeightCascade(rightPtr);
			return true;
		}
		return false;
	}

	bool RotateRight(NodeHandle ndHd)
	{
		auto nodePtr = GetNode(ndHd);
		if(nullptr != nodePtr && nullptr != nodePtr->left)
		{
			auto leftPtr = nodePtr->left;
			auto RightofLeft = nodePtr->left->right;

			if(nullptr == nodePtr->up)
			{
				root = leftPtr;
				leftPtr->up = nullptr;
			}
			else
			{
				leftPtr->up = nodePtr->up;
				if(nodePtr->up->left == nodePtr)
				{
					nodePtr->up->left = leftPtr;
				}
				else
				{
					nodePtr->up->right = leftPtr;
				}
			}

			leftPtr->right = nodePtr;
			nodePtr->up = leftPtr;

			nodePtr->left = RightofLeft;
			if(nullptr != RightofLeft)
			{
				RightofLeft->up = nodePtr;
			}
			UpdateHeight(nodePtr);
			UpdateHeightCascade(leftPtr);
			return true;
		}
		return false;
	}

	bool TreeToVine(NodeHandle ndHd)
	{
		// Node *vine_tail = new Node();
		// vine_tail->right = ndHd.ptr;
		auto vine_tail = GetNode(ndHd);
		auto Remainder = vine_tail->right;
		if(nullptr == Remainder) return false;
		while(Remainder)
		{
			// Remainder = vine_tail->right;
			if(Remainder->left)
			{
				NodeHandle node;
				node.ptr = Remainder;
				RotateRight(node);
				Remainder = vine_tail->right;
			}
			else
			{
				vine_tail = Remainder;
				Remainder = vine_tail->right;
			}
		}
		return true;
	}


	// bool TreeToVine(NodeHandle ndHd)
	// {
	// 	// Node *vine_tail = new Node();
	// 	// vine_tail->right = ndHd.ptr;
	// 	auto vine_tail = GetNode(ndHd);
	// 	auto Remainder = vine_tail->right;
	// 	int size = 0;
	// 	if(!Remainder) return false;
	// 	while(Remainder)
	// 	{
	// 		if(!Remainder->left)
	// 		{
	// 			vine_tail = Remainder;
	// 			Remainder = Remainder->right;
	// 			size++;
	// 		}
	// 		else
	// 		{
	// 			auto tmpPtr = Remainder->left;
	// 			Remainder->left = tmpPtr->right;
	// 			tmpPtr->right = Remainder;
	// 			Remainder = tmpPtr;
	// 			vine_tail->right = tmpPtr;
	// 			UpdateHeight(Remainder);
	// 			UpdateHeightCascade(Remainder);

	// 		}
	// 	}
	// 	UpdateHeight(vine_tail);
	// 	UpdateHeightCascade(vine_tail);
	// 	return true;
	// }

	bool compress(Node* fake_root, int count)
	{
		if(!fake_root)
		{
			printf("visiting nullptr.");
			return false;
		}
		auto scanner = fake_root;
		Node *child;
		NodeHandle tmpNode;
		for(int i=0;i<count;++i)
		{
			// child = scanner->right;
			// scanner->right = child->right;
			// scanner = scanner->right;
			// child->right = scanner->left;
			// scanner->left = child;
			// UpdateHeight(scanner->up);
			// UpdateHeightCascade(child);
			tmpNode.ptr = scanner->right;
			RotateLeft(tmpNode);
			scanner = scanner->right;
		}
		return true;
	}

	bool IsVine(NodeHandle ndHd) const
	{
		auto root = ndHd.ptr->right;
		while(root)
		{
			if(root->left) return false;
			root = root->right;
		}
		return true;
	}

	bool VineToTree(NodeHandle ndHd, int size) // size means number of nodes in the vine
	{
		int leaf_count = size + 1 - pow(2, floor(log2(size + 1)));
		auto fake_root = GetNode(ndHd);
		// Node *root = new Node();
		// root->right = GetNode(ndHd);
		compress(fake_root, leaf_count);
		size -= leaf_count;
		while(size > 1)
		{
			printf("%i\n", size);
			compress(fake_root, size / 2);
			size /= 2;
		}
		// delete root;
		return true;
	}
};


