struct vantage_pt_tree{

	struct node{
		pt p;
		double th;
		node *l, *r;
	}*root;

	vector<pair<double, pt>> aux;

	vantage_pt_tree(vector<pt> &ps){
		forn(i, sz(ps)) aux.pb({0, ps[i]});
		root = build(0, sz(ps));
	}

	node *build(int l, int r){
		if (l == r) return 0;

		swap(aux[l], aux[l + rand() % (r - l)]);
		pt p = aux[l++].second;
		if (l == r) return new node({ p });

		fore(i,l, r-1)  aux[i].fi = (p - aux[i].second).norm2();
		int m = (l + r) / 2;
		nth_element(aux.begin() + l, aux.begin() + m, aux.begin() + r);
		return new node({ p, sqrt(aux[m].first), build(l, m), build(m, r) });
	}

	priority_queue<pair<double, node*>> que;

	void k_nn(node *t, pt p, int k){
		if (!t) return;

		double d = (p - t->p).norm();
		if(sz(que) < k) que.push({d, t});
		else if (que.top().fi > d){
			que.pop();
			que.push({d, t});
		}

		if (!t->l && !t->r) return;

		if (d < t->th){
			k_nn(t->l, p, k);
			if (t->th - d <= que.top().fi)
        k_nn(t->r, p, k);
		}else{
			k_nn(t->r, p, k);
			if (d - t->th <= que.top().fi)
				k_nn(t->l, p, k);
		}
	}

	vector<pt> k_nn(pt p, int k){
		k_nn(root, p, k);
		vector<pt> ans;
		for (; !que.empty(); que.pop())
			ans.pb(que.top().se->p);
		reverse(all(ans));
		return ans;
	}
};
